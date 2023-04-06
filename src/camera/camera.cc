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
  height_constant_ = map::kBlockSize * (static_cast<double>(this->GetSceneHeight()) / 2.) / 1.732050;
  distance_from_projection_plane_ =
      (static_cast<double>(this->GetSceneWidth()) / 2.)
          / std::tan(geometry::k60_degree); //TODO lockup table for tan;
  pixels_ = std::vector<unsigned char>(this->GetSceneWidth() * this->GetSceneHeight() * 3, 0);
}

double Camera::GetFovInRadians() const {
  return kFOV_;
}

position::Position Camera::GetPosition() {
  return position_;
}

double Camera::GetCameraHeight() const {
  return camera_height_;
}

int Camera::GetSceneWidth() const {
  return scene_width_;
}

int Camera::GetSceneHeight() const {
  return scene_height_;
}

double Camera::GetHeightConstant() const {
  return height_constant_;
}

double Camera::GetDistanceFromProjectionPlane() const {
  return distance_from_projection_plane_;
}

double Camera::GetLightSourceConstant() const {
  return light_source_constant_;
}

double Camera::GetMoveStep() const {
  return move_step_;
}

void Camera::Draw(int columns_number, int columns_height, map::Map &map) {
  double ray_step = camera::Camera::GetFovInRadians() / columns_number;
  double angle = GetFacingDirectionInRadians() - (camera::Camera::GetFovInRadians() / 2);

  for (int current_column = columns_number; current_column > 0; --current_column) {
    angle += ray_step;
    DrawColumn(current_column, angle, columns_height, map);
  }
}

void Camera::DrawColumn(int column, double angle, int columns_height, map::Map &map) {
  position::Position
      horizontal_intersection = geometry::findHorizontalWallIntersection(GetPosition(), angle, map);
  position::Position vertical_intersection = geometry::findVerticalWallIntersection(GetPosition(), angle, map);

  double horizontal_distance = geometry::findDistance(horizontal_intersection, GetPosition());
  double vertical_distance = geometry::findDistance(vertical_intersection, GetPosition());

  auto min_distance = vertical_distance;
  auto nearest_intersection = vertical_intersection.y;

  if (horizontal_distance < vertical_distance) {
    min_distance = horizontal_distance;
    nearest_intersection = horizontal_intersection.x;
  }

  auto texture_column = static_cast<int>(nearest_intersection) % static_cast<int>(map::kBlockSize);

  double height = GetHeightConstant() / min_distance;
  double light_intensity = GetLightIntensity(min_distance);

  SetColorLine(
      column,
      (int) floor((columns_height - height) / 2),
      (int) ((columns_height + height) / 2),
      GetTexture(0), //TODO chose how to select textures dinamically
      light_intensity,
      texture_column);

  double beta = std::abs(angle - GetFacingDirectionInRadians());
  DrawFloor(column, beta, columns_height, height, angle);
  DrawCeiling(column, columns_height, height);
}

void Camera::DrawFloor(int current_column, double beta, int columns_height, double height, double angle) {
  double straight_line_distance, real_distance, light_intensity;

  for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
    straight_line_distance =
        GetDistanceFromProjectionPlane() * GetCameraHeight()
            / (current_row - (static_cast<double>(columns_height) / 2.)); // TODO extract this function
    real_distance = straight_line_distance / cos(beta);
    light_intensity = GetLightIntensity(real_distance);

    double yEnd = straight_line_distance * sin(angle) + GetPosition().y;
    double xEnd = straight_line_distance * cos(angle) - GetPosition().x;

    color::ColorRGB color = GetTexture(1).getColor(geometry::Mod(xEnd, map::kBlockSize),
                                                   geometry::Mod(yEnd, map::kBlockSize));

    SetColor(current_column, current_row, color, light_intensity);
  }
}

void Camera::DrawCeiling(int current_column, int columns_height, double height) {
  for (int current_row = (int) ((columns_height + height) / 2.); current_row < GetSceneHeight(); ++current_row) {
    SetColor(current_column, current_row, color::kBlack, 1.);
  }
}

void Camera::SetColorLine(int column,
                          int bottom,
                          int top,
                          const texture::Texture &texture,
                          double intensity,
                          int texture_vertical_coordinate) {
  for (int i = top, range_size = top - bottom; i > bottom; --i) {
    SetColor(column,
             i,
             texture.getColor(texture_vertical_coordinate, MapToTileSize(i - bottom, range_size, map::kBlockSize))
                 * intensity);
  }
}

void Camera::SetColor(int column, int row, color::ColorRGB color) {
  auto index = (column + (row * GetSceneWidth())) * 3;
  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

void Camera::SetColor(int column, int row, color::ColorRGB color, double intensity) {
  SetColor(column, row, color * intensity);
}

void Camera::MoveLeft() {
  position_.x -= GetMoveStep();
}

void Camera::MoveRight() {
  position_.x += GetMoveStep();
}

void Camera::MoveBackward() {
  position_.y += GetMoveStep();
}

void Camera::MoveForward() {
  position_.y -= GetMoveStep();
}

void Camera::RotateLeft() {
  view_direction_in_radians_ += GetRotationStep();
  if (view_direction_in_radians_ > geometry::k359_degree) view_direction_in_radians_ = geometry::k1_degree;
}

void Camera::RotateRight() {
  view_direction_in_radians_ -= GetRotationStep();
  if (view_direction_in_radians_ < geometry::k1_degree) view_direction_in_radians_ = geometry::k359_degree;
}

double Camera::GetFacingDirectionInRadians() const {
  return view_direction_in_radians_;
}

void Camera::Move(int key) {
  switch (key) {
    case (GLFW_KEY_Q): RotateLeft();
      break;
    case (GLFW_KEY_W): MoveForward();
      break;
    case (GLFW_KEY_E): RotateRight();
      break;
    case (GLFW_KEY_A): MoveLeft();
      break;
    case (GLFW_KEY_S): MoveBackward();
      break;
    case (GLFW_KEY_D): MoveRight();
      break;
    default:break;
  }
}

std::vector<unsigned char> &Camera::GetPixels() {
  return pixels_;
}

double Camera::GetLightIntensity(double distance) const {
  return std::min((GetLightSourceConstant() / std::pow(distance, 2)), 1.);
}

void Camera::LoadTexture(const char *path) {
  textures_.emplace_back(path);
}

texture::Texture Camera::GetTexture(int index) {
  return textures_[index];
}
double Camera::GetRotationStep() const {
  return rotation_step_;
}

int MapToTileSize(double coordinate, double range_size, double tile_size) {
  return static_cast<int>(coordinate / range_size * --tile_size);
}
}
