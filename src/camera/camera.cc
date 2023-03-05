//
// Created by Stefano on 3/4/2023.
//

#include "camera.h"

namespace camera {
void Camera::moveLeft() {
  position_.x += MOVE_CONSTANT;
}

void Camera::moveRight() {
  position_.x -= MOVE_CONSTANT;
}

void Camera::moveBackward() {
  position_.y += MOVE_CONSTANT;
}

void Camera::moveForward() {
  position_.y -= MOVE_CONSTANT;
}

void Camera::rotateLeft() {
  view_direction_ -= ROTATE_CONSTANT;
}

void Camera::rotateRight() {
  view_direction_ += ROTATE_CONSTANT;
}

float Camera::getFacingDirection() const {
  return view_direction_;
}
Camera::Camera() {
  view_direction_ = 90;
  position_ = {
      .x = 224, .y = 224
  };
  FOV_ = 60.0f;
  height_ = 60;
}

void Camera::move(int key) {
  switch (key) {
    case (Q_KEY_PRESSED): rotateLeft();
      break;
    case (W_KEY_PRESSED): moveForward();
      break;
    case (E_KEY_PRESSED): rotateRight();
      break;
    case (A_KEY_PRESSED): moveLeft();
      break;
    case (S_KEY_PRESSED): moveBackward();
      break;
    case (D_KEY_PRESSED): moveRight();
      break;
    default:break;
  }
}

float Camera::getFOV() const {
  return FOV_;
}

Position Camera::getPosition() {
  return position_;
}
}
