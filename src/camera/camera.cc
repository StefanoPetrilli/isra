//
// Created by Stefano on 3/4/2023.
//

#include "camera.h"

namespace camera {

void Camera::draw(int columns_number,
                  int columns_height,
                  camera::Camera *camera,
                  std::vector<unsigned char> &pixels,
                  map::Map &map) {
  double ray_step = camera::Camera::getFOVInRadians() / columns_number;
  double angle = camera->getFacingDirectionInRadians() - (camera::Camera::getFOVInRadians() / 2);

  for (int current_column = columns_number; current_column > 0; angle += ray_step, --current_column) {
    drawColumn(current_column, angle, columns_height, camera, pixels, map);
  }
}

void Camera::drawColumn(int current_column,
                        double angle,
                        int columns_height,
                        Camera *camera,
                        std::vector<unsigned char> &pixels,
                        map::Map &map) {
  position::Position
      horizontal_intersection = geometry::findHorizontalWallIntersection(camera->getPosition(), angle, map);
  position::Position vertical_intersection = geometry::findVerticalWallIntersection(camera->getPosition(), angle, map);

  double horizontal_distance = geometry::findDistance(horizontal_intersection, camera->getPosition());
  double vertical_distance = geometry::findDistance(vertical_intersection, camera->getPosition());

  auto min_distance = std::min(horizontal_distance, vertical_distance);
  double height = kHeightConstant / min_distance;
  double light_intensity = getLightIntensity(min_distance);
  setColorLine(pixels,
               current_column,
               (int) floor((columns_height - height) / 2),
               (int) ((columns_height + height) / 2),
               color::kRed,
               light_intensity);

  double beta = std::abs(angle - camera->getFacingDirectionInRadians());
  drawFloor(current_column, beta, columns_height, height, camera, pixels);
  drawCeiling(current_column, beta, columns_height, height, camera, pixels);
}

void Camera::drawFloor(int current_column,
                       double beta,
                       int columns_height,
                       double height,
                       Camera *camera,
                       std::vector<unsigned char> &pixels) {
  double straight_line_distance, real_distance, light_intensity;

  for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
    straight_line_distance =
        kDistanceFromProjectionPlane_ * camera->getHeight() / (current_row - (columns_height / 2));
    real_distance = straight_line_distance / cos(beta);
    light_intensity = getLightIntensity(real_distance);
    setColor(current_column, current_row, pixels, color::kGreen, light_intensity);
  }
}

void Camera::drawCeiling(int current_column,
                         double beta,
                         int columns_height,
                         double height,
                         Camera *camera,
                         std::vector<unsigned char> &pixels) {
  double straight_line_distance, real_distance, light_intensity;

  for (int current_row = (int) ((columns_height + height) / 2); current_row < kWindow_Height; ++current_row) {
    straight_line_distance =
        kDistanceFromProjectionPlane_ * camera->getHeight() / (current_row - (columns_height / 2));
    real_distance = straight_line_distance / cos(beta);
    light_intensity = getLightIntensity(real_distance);
    setColor(current_column, current_row, pixels, color::kBlue, light_intensity);
  }
}

void Camera::setColorLine(std::vector<unsigned char> &pixels, int column, int bottom, int top, color::ColorRGB color) {
  for (int i = top; i > bottom; --i) {
    setColor(column, i, pixels, color);
  }
}

void Camera::setColorLine(std::vector<unsigned char> &pixels,
                          int column,
                          int bottom,
                          int top,
                          color::ColorRGB color,
                          double intensity) {
  setColorLine(pixels, column, bottom, top, color * intensity);
}

void Camera::setColor(int column, int row, std::vector<unsigned char> &pixels, color::ColorRGB color) {
  auto index = (column + (row * camera::kWindow_Width)) * 3;
  pixels[index] = color.r;
  pixels[index + 1] = color.g;
  pixels[index + 2] = color.b;
}

void Camera::setColor(int column,
                      int row,
                      std::vector<unsigned char> &pixels,
                      color::ColorRGB color,
                      double intensity) {
  setColor(column, row, pixels, color * intensity);
}

void Camera::moveLeft() {
  position_.x -= MOVE_CONSTANT;
}

void Camera::moveRight() {
  position_.x += MOVE_CONSTANT;
}

void Camera::moveBackward() {
  position_.y += MOVE_CONSTANT;
}

void Camera::moveForward() {
  position_.y -= MOVE_CONSTANT;
}

void Camera::rotateLeft() {
  view_direction_in_radians_ += ROTATE_CONSTANT;
  if (view_direction_in_radians_ > 6.2831853072f) view_direction_in_radians_ = 0.0f;
}

void Camera::rotateRight() {
  view_direction_in_radians_ -= ROTATE_CONSTANT;
  if (view_direction_in_radians_ < 0.0f) view_direction_in_radians_ = 6.2831853072f;
}

double Camera::getFacingDirectionInRadians() const {
  return view_direction_in_radians_;
}
Camera::Camera() {
  pixels_ = std::vector<unsigned char>(kWindow_Width * kWindow_Height * 3, 0);
  view_direction_in_radians_ = 1.5707963268f;
  position_ = {
      .x = 100.0f, .y = 350.0f
  };
  height_ = 60.0f;
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

double Camera::getFOVInRadians() {
  return kFOV_;
}

position::Position Camera::getPosition() {
  return position_;
}
double Camera::getHeight() const {
  return height_;
}

std::vector<unsigned char> &Camera::GetPixels() {
  return pixels_;
}

double Camera::getLightIntensity(double distance) {
  return std::min((kLight_Source_Constant / std::pow(distance, 2)), 1.0);
}

}
