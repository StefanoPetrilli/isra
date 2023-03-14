//
// Created by Stefano on 3/4/2023.
//

#include "camera.h"

namespace camera {

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
  view_direction_in_radians_ = 1.5707963268f;
  position_ = {
      .x = 115.0f, .y = 224.0f
  };
  height_ = 60.0f;
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

double Camera::getFOVInRadians() {
  return kFOV_;
}

double Camera::GetDistanceFromProjectionPlane() {
  return kDistanceFromProjectionPlane_;
}

Position Camera::getPosition() {
  return position_;
}
double Camera::getHeight() {
  return height_;
}
double Camera::getDistanceFromProjectionPlane() {
  return kDistanceFromProjectionPlane_;
}
}
