//
// Created by Stefano on 3/4/2023.
//

#include "camera.h"

namespace camera {

Camera::Camera(int scene_width, int scene_height, double camera_height) {
  view_direction_in_radians_ = 0.;
  position_ = {
      .x = 100., .y = 100.
  };
  scene_height_ = scene_height;
  scene_width_ = scene_width;
  engine_ = rendering_engine::RenderingEngine(scene_width, scene_height, camera_height);
}

double Camera::GetFovInRadians() const {
  return kFOV_;
}

position::Position Camera::GetPosition() {
  return position_;
}

int Camera::GetSceneWidth() const {
  return scene_width_;
}

int Camera::GetSceneHeight() const {
  return scene_height_;
}

double Camera::GetMoveStep() const {
  return move_step_;
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
  view_direction_in_radians_ = geometry::dmod(view_direction_in_radians_ + GetRotationStep(), geometry::k359_degree);
}

void Camera::RotateRight() {
  view_direction_in_radians_ = geometry::dmod(view_direction_in_radians_ - GetRotationStep(), geometry::k359_degree);
}

double Camera::GetFacingDirectionInRadians() const {
  return view_direction_in_radians_;
}

std::vector<unsigned char> &Camera::GetPixels() {
  return engine_.GetPixels();
}

double Camera::GetRotationStep() const {
  return rotation_step_;
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

void Camera::Draw(map::Map &map) {
  engine_.Draw(GetSceneWidth(), GetSceneHeight(), GetFovInRadians(), map, GetFacingDirectionInRadians(), GetPosition());
}
}
