//
// Created by Stefano on 3/4/2023.
//

#include "camera.h"

namespace camera {
Camera::Camera(int scene_width, int scene_height, double camera_height) {
  view_direction_in_radians_ = geometry::k90_degree;
  position_ = {
      .x = 100.0, .y = 350.0
  };
  camera_height_ = camera_height;
  scene_height_ = scene_height;
  scene_width_ = scene_width;
  height_constant_ = map::kBlockSize * (static_cast<double>(this->getSceneHeight()) / 2.) / 1.732050;
  distance_from_projection_plane_ =
      (static_cast<double>(this->getSceneWidth()) / 2.)
          / std::tan(geometry::k60_degree); //TODO lockup table for tan;
  pixels_ = std::vector<unsigned char>(this->getSceneWidth() * this->getSceneHeight() * 3, 0);
}

double Camera::getFOVInRadians() const {
  return kFOV_;
}

position::Position Camera::getPosition() {
  return position_;
}

double Camera::getCameraHeight() const {
  return camera_height_;
}

int Camera::getSceneWidth() const {
  return scene_width_;
}

int Camera::getSceneHeight() const {
  return scene_height_;
}

double Camera::getHeightConstant() const {
  return height_constant_;
}

double Camera::getDistanceFromProjectionPlane() const {
  return distance_from_projection_plane_;
}

double Camera::getLightSourceConstant() const {
  return light_source_constant_;
}

double Camera::getMoveStep() const {
  return move_step_;
}

void Camera::draw(int columns_number, int columns_height, map::Map &map) {
  double ray_step = camera::Camera::getFOVInRadians() / columns_number;
  double angle = getFacingDirectionInRadians() - (camera::Camera::getFOVInRadians() / 2);

  for (int current_column = columns_number; current_column > 0; --current_column) {
    angle += ray_step;
    drawColumn(current_column, angle, columns_height, map);
  }
}

void Camera::drawColumn(int current_column, double angle, int columns_height, map::Map &map) {
  position::Position
      horizontal_intersection = geometry::findHorizontalWallIntersection(getPosition(), angle, map);
  position::Position vertical_intersection = geometry::findVerticalWallIntersection(getPosition(), angle, map);

  double horizontal_distance = geometry::findDistance(horizontal_intersection, getPosition());
  double vertical_distance = geometry::findDistance(vertical_intersection, getPosition());

  auto min_distance = vertical_distance;
  auto nearest_intersection = vertical_intersection.y;

  if (horizontal_distance < vertical_distance) {
    min_distance = horizontal_distance;
    nearest_intersection = horizontal_intersection.x;
  }

  auto texture_column = static_cast<int>(nearest_intersection) % static_cast<int>(map::kBlockSize);

  double height = getHeightConstant() / min_distance;
  double light_intensity = getLightIntensity(min_distance);

  setColorLine(
      current_column,
      (int) floor((columns_height - height) / 2),
      (int) ((columns_height + height) / 2),
      getTexture(0), //TODO chose how to select textures dinamically
      light_intensity,
      texture_column);

  double beta = std::abs(angle - getFacingDirectionInRadians());
  drawFloor(current_column, beta, columns_height, height, angle);
  drawCeiling(current_column, beta, columns_height, height);
}

void Camera::drawFloor(int current_column, double beta, int columns_height, double height, double angle) {
  double straight_line_distance, real_distance, light_intensity;

  for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
    straight_line_distance =
        getDistanceFromProjectionPlane() * getCameraHeight()
            / (current_row - (static_cast<double>(columns_height) / 2.)); // TODO extract this function
    real_distance = straight_line_distance / cos(beta);
    light_intensity = getLightIntensity(real_distance);

    double yEnd = straight_line_distance * sin(angle) + getPosition().y;
    double xEnd = straight_line_distance * cos(angle) - getPosition().x;

    color::ColorRGB color = getTexture(1).getColor(geometry::Mod(xEnd, map::kBlockSize),
                                                   geometry::Mod(yEnd, map::kBlockSize));

    setColor(current_column, current_row, color, light_intensity);
  }
}

void Camera::drawCeiling(int current_column, double beta, int columns_height, double height) {
  double straight_line_distance, real_distance, light_intensity;

  for (int current_row = (int) ((columns_height + height) / 2.); current_row < getSceneHeight(); ++current_row) {
    straight_line_distance =
        getDistanceFromProjectionPlane() * getCameraHeight()
            / (current_row - (static_cast<double>(columns_height) / 2.));
    real_distance = straight_line_distance / cos(beta);
    light_intensity = getLightIntensity(real_distance);
    setColor(current_column, current_row, color::kBlue, light_intensity);
  }
}

void Camera::setColorLine(int column,
                          int bottom,
                          int top,
                          const texture::Texture &texture,
                          double intensity,
                          int texture_vertical_coordinate) {
  for (int i = top, range_size = top - bottom; i > bottom; --i) {
    setColor(column,
             i,
             texture.getColor(texture_vertical_coordinate, MapToTileSize(i - bottom, range_size, map::kBlockSize))
                 * intensity);
  }
}

void Camera::setColor(int column, int row, color::ColorRGB color) {
  auto index = (column + (row * getSceneWidth())) * 3;
  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

void Camera::setColor(int column, int row, color::ColorRGB color, double intensity) {
  setColor(column, row, color * intensity);
}

void Camera::moveLeft() {
  position_.x -= getMoveStep();
}

void Camera::moveRight() {
  position_.x += getMoveStep();
}

void Camera::moveBackward() {
  position_.y += getMoveStep();
}

void Camera::moveForward() {
  position_.y -= getMoveStep();
}

void Camera::rotateLeft() {
  view_direction_in_radians_ += getRotationStep();
  if (view_direction_in_radians_ > geometry::k359_degree) view_direction_in_radians_ = geometry::k1_degree;
}

void Camera::rotateRight() {
  view_direction_in_radians_ -= getRotationStep();
  if (view_direction_in_radians_ < geometry::k1_degree) view_direction_in_radians_ = geometry::k359_degree;
}

double Camera::getFacingDirectionInRadians() const {
  return view_direction_in_radians_;
}

void Camera::move(int key) {
  switch (key) {
    case (GLFW_KEY_Q): rotateLeft();
      break;
    case (GLFW_KEY_W): moveForward();
      break;
    case (GLFW_KEY_E): rotateRight();
      break;
    case (GLFW_KEY_A): moveLeft();
      break;
    case (GLFW_KEY_S): moveBackward();
      break;
    case (GLFW_KEY_D): moveRight();
      break;
    default:break;
  }
}

std::vector<unsigned char> &Camera::GetPixels() {
  return pixels_;
}

double Camera::getLightIntensity(double distance) const {
  return std::min((getLightSourceConstant() / std::pow(distance, 2)), 1.);
}

void Camera::loadTexture(const char *path) {
  textures_.emplace_back(path);
}

texture::Texture Camera::getTexture(int index) {
  return textures_[index];
}
double Camera::getRotationStep() const {
  return rotation_step_;
}

int MapToTileSize(double coordinate, double range_size, double tile_size) {
  return static_cast<int>(coordinate / range_size * --tile_size);
}
}
