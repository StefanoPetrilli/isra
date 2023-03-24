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
  double ray_step = camera::Camera::getFOVInRadians() / columns_number,
      angle = camera->getFacingDirectionInRadians() - (camera::Camera::getFOVInRadians() / 2),
      horizontal_distance, vertical_distance, height, straight_line_distance, real_distance, beta;
  int wall_bottom;

  position::Position horizontal_intersection{}, vertical_intersection{};

  for (int current_column = columns_number; current_column > 0; angle += ray_step, --current_column) {
    horizontal_intersection = geometry::findHorizontalWallIntersection(camera->getPosition(), angle, map);
    vertical_intersection = geometry::findVerticalWallIntersection(camera->getPosition(), angle, map);

    horizontal_distance = geometry::findDistance(horizontal_intersection, camera->getPosition());
    vertical_distance = geometry::findDistance(vertical_intersection, camera->getPosition());

    auto min = horizontal_distance < vertical_distance ? horizontal_distance : vertical_distance;
    height = kHeightConstant / min;
    wall_bottom = floor((columns_height - height) / 2);
    setColorLine(pixels,
                 current_column,
                 wall_bottom,
                 (int) ((columns_height + height) / 2),
                 255,
                 0,
                 0);
    beta = abs(angle - camera->getFacingDirectionInRadians());
    for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
      straight_line_distance =
          kDistanceFromProjectionPlane_ * camera->getHeight() / (current_row - (columns_height / 2));
      real_distance = straight_line_distance / cos(beta);
      setColor(current_column, current_row, pixels, 0, 255, 0);
    }
  }
}
void Camera::setColorLine(std::vector<unsigned char> &pixels,
                          int column,
                          int bottom,
                          int top,
                          unsigned char r,
                          unsigned char g,
                          unsigned char b) {
  for (int i = top; i > bottom; --i) {
    setColor(column, i, pixels, r, g, b);
  }
}

void Camera::setColor(int column,
                      int row,
                      std::vector<unsigned char> &pixels,
                      unsigned char r,
                      unsigned char g,
                      unsigned char b) {
  auto index = (column + (row * camera::kWindow_Width)) * 3;
  pixels[index] = r;
  pixels[index + 1] = g;
  pixels[index + 2] = b;
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

void Camera::FlushPixels() {
  std::fill(pixels_.begin(), pixels_.end(), 0);
}
}
