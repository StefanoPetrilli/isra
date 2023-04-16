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
  camera_height_ = camera_height;
  scene_height_ = scene_height;
  scene_height_ = scene_height;
  scene_width_ = scene_width;
  height_constant_ = map::kBlockSize * (static_cast<double>(this->GetSceneHeight()) / 2.) / 1.732050;
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

double Camera::GetHeightConstant() const {
  return height_constant_;
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

void Camera::Draw(int columns_number, int columns_height, map::Map &map) {
  double ray_step = camera::Camera::GetFovInRadians() / columns_number;
  double angle = GetFacingDirectionInRadians() - (camera::Camera::GetFovInRadians() / 2);

  for (int current_column = columns_number; current_column > 0; --current_column) {
    angle = geometry::dmod(angle + ray_step, geometry::k359_degree);
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
  double light_intensity = engine_.GetLightIntensity(min_distance);

  engine_.SetColorLine(
      column,
      (int) floor((columns_height - height) / 2),
      (int) ((columns_height + height) / 2),
      rendering_engine::RenderingEngine::GetTexture(0), //TODO chose how to select textures dinamically
      light_intensity,
      texture_column);

  double beta = std::abs(angle - GetFacingDirectionInRadians());
  engine_.DrawFloor(column, beta, columns_height, height, angle, GetPosition());
  engine_.DrawCeiling(column, columns_height, height);
}
}
