//
// Created by Stefano on 4/16/2023.
//

#include "rendering_engine.h"

namespace rendering_engine {
std::vector<texture::Texture> RenderingEngine::textures_;

rendering_engine::RenderingEngine::RenderingEngine(int scene_width,
                                                   int scene_height,
                                                   double camera_height,
                                                   double fov,
                                                   map::Map map) {
  scene_width_ = scene_width;
  scene_height_ = scene_height;
  camera_height_ = camera_height;
  fov_ = fov;
  ray_step_ = fov / scene_width;
  pixels_ = std::vector<color::ColorRGB>(scene_width * scene_height + 1, color::kBlack);
  distance_from_projection_plane_ = (static_cast<double>(scene_width) / 2.) / std::tan(geometry::k60_degree);
  straight_line_distance_constant_ = camera_height_ * distance_from_projection_plane_;
  map_ = map;
  height_constant_ = map::kBlockSize * (static_cast<double>(this->GetSceneHeight()) / 2.) / 1.732050;
  distance_shader_ =
      distance_shader::DistanceShader(
          std::max(map.GetWidth() * map::kBlockSizeInt, map.GetHeight()) * map::kBlockSizeInt);
}

void RenderingEngine::Draw(double facing_direction, position::Position position) {
  double starting_angle = facing_direction - (GetFov() / 2);
  memset(&pixels_[0], 0, pixels_.size() * sizeof pixels_[0]);

  for (int current_column = GetSceneWidth(); current_column > 0; --current_column)
    DrawColumn(current_column,
               geometry::dmod(starting_angle + (GetRayStep() * current_column), geometry::k359_degree),
               GetSceneHeight(),
               position);
}

void RenderingEngine::ParallelDraw(double facing_direction, position::Position position) {
  double starting_angle = facing_direction - (GetFov() / 2);
  memset(&pixels_[0], 0, pixels_.size() * sizeof pixels_[0]);

#pragma omp parallel shared(starting_angle, position) default(none)
  {
#pragma omp for
    for (int current_column = GetSceneWidth(); current_column > 0; --current_column)
      DrawColumn(current_column,
                 geometry::dmod(starting_angle + (GetRayStep() * current_column), geometry::k359_degree),
                 GetSceneHeight(),
                 position);
  }
}

void RenderingEngine::DrawColumn(int column, double angle, int columns_height, position::Position position) {
  position::Position horizontal_intersection = geometry::findHorizontalWallIntersection(position, angle, GetMap());
  position::Position vertical_intersection = geometry::findVerticalWallIntersection(position, angle, GetMap());

  double horizontal_distance = geometry::findDistance(horizontal_intersection, position);
  double vertical_distance = geometry::findDistance(vertical_intersection, position);

  auto min_distance = vertical_distance;
  auto nearest_intersection = vertical_intersection.y;

  if (horizontal_distance < vertical_distance) {
    min_distance = horizontal_distance;
    nearest_intersection = horizontal_intersection.x;
  }

  min_distance = sqrt(min_distance);
  double height = GetHeightConstant() / min_distance;

  SetColorLine(
      column,
      static_cast<int>(floor((columns_height - height) / 2)),
      static_cast<int>((columns_height + height) / 2),
      rendering_engine::RenderingEngine::GetTexture(0), //TODO chose how to select textures dynamically
      distance_shader_.GetIntensity(std::abs(static_cast<int>(min_distance))),
      static_cast<int>(nearest_intersection) % map::kBlockSizeInt);

  DrawFloor(column, columns_height, height, angle, position);
}

void RenderingEngine::DrawFloor(int current_column,
                                int columns_height,
                                double height,
                                double angle,
                                position::Position position) {
  double straight_line_distance, x_texture, y_texture;
  double sin_angle = sin(angle), cos_angle = cos(angle);
  double half_columns_height = columns_height >> 1;
  unsigned short light_intensity;

  for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
    straight_line_distance = GetStraightLineDistanceConstant() / (current_row - half_columns_height);
    light_intensity = distance_shader_.GetIntensity(std::abs(static_cast<int>(straight_line_distance)));

    y_texture = straight_line_distance * sin_angle + position.y;
    x_texture = straight_line_distance * cos_angle - position.x;

    color::ColorRGB color = rendering_engine::RenderingEngine::GetTexture(1)
        .GetColor(std::abs(static_cast<int>(x_texture)) % map::kBlockSizeInt,
                  std::abs(static_cast<int>(y_texture)) % map::kBlockSizeInt);

    SetColor(current_column, current_row, color, light_intensity);
  }
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color, const unsigned short intensity) {
  SetColor(column, row, color * intensity);
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color) {
  auto index = column + (row * GetSceneWidth());
  pixels_[index] = color;
}

void RenderingEngine::SetColorLine(int column,
                                   int bottom,
                                   int top,
                                   const texture::Texture &texture,
                                   const unsigned short intensity,
                                   int texture_vertical_coordinate) {
  for (int i = top, range_size = top - bottom; i > bottom; --i) {
    SetColor(column,
             i,
             texture.GetColor(texture_vertical_coordinate,
                              MapToTileSize(i - bottom, range_size, map::kBlockSize))
                 * intensity);
  }
}

int MapToTileSize(double coordinate, double range_size, double tile_size) {
  return static_cast<int>(coordinate / range_size * --tile_size);
}

std::vector<color::ColorRGB> &RenderingEngine::GetPixels() {
  return pixels_;
}

void RenderingEngine::LoadTexture(const char *path) {
  textures_.emplace_back(path);
}

texture::Texture &RenderingEngine::GetTexture(int index) {
  return textures_[index];
}

int RenderingEngine::GetSceneWidth() const {
  return scene_width_;
}

int RenderingEngine::GetSceneHeight() const {
  return scene_height_;
}

double RenderingEngine::GetHeightConstant() const {
  return height_constant_;
}

map::Map &RenderingEngine::GetMap() {
  return map_;
}

double RenderingEngine::GetStraightLineDistanceConstant() const {
  return straight_line_distance_constant_;
}

double RenderingEngine::GetRayStep() const {
  return ray_step_;
}

double RenderingEngine::GetFov() const {
  return fov_;
}
}
