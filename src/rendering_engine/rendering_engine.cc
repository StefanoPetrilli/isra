//
// Created by Stefano on 4/16/2023.
//

#include "rendering_engine.h"

namespace rendering_engine {
std::vector<texture::Texture> RenderingEngine::textures_;

rendering_engine::RenderingEngine::RenderingEngine(int scene_width, int scene_height, double camera_height) {
  scene_width_ = scene_width;
  scene_height_ = scene_height;
  camera_height_ = camera_height;
  pixels_ = std::vector<unsigned char>(scene_width * scene_height * 3, 0);
  distance_from_projection_plane_ =
      (static_cast<double>(this->GetSceneWidth()) / 2.)
          / std::tan(geometry::k60_degree); //TODO lockup table for tan;
  height_constant_ = map::kBlockSize * (static_cast<double>(this->GetSceneHeight()) / 2.) / 1.732050;
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color, double intensity) {
  SetColor(column, row, color * intensity);
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color) {
  auto index = (column + (row * GetSceneWidth())) * 3;
  pixels_[index] = color.r;
  pixels_[index + 1] = color.g;
  pixels_[index + 2] = color.b;
}

void RenderingEngine::SetColorLine(int column,
                                   int bottom,
                                   int top,
                                   const texture::Texture &texture,
                                   double intensity,
                                   int texture_vertical_coordinate) {
  for (int i = top, range_size = top - bottom; i > bottom; --i) {
    SetColor(column,
             i,
             texture.getColor(texture_vertical_coordinate, MapToTileSize(i - bottom, range_size, 64)) //TODO
                 * intensity);
  }
}

std::vector<unsigned char> &RenderingEngine::GetPixels() {
  return pixels_;
}

void RenderingEngine::LoadTexture(const char *path) {
  textures_.emplace_back(path);
}

texture::Texture &RenderingEngine::GetTexture(int index) {
  return textures_.at(index);
}

double RenderingEngine::GetLightSourceConstant() {
  return 4000.;
}

double RenderingEngine::GetLightIntensity(double distance) const {
  return std::min((GetLightSourceConstant() / std::pow(distance, 2)), 1.);
}

int RenderingEngine::GetSceneWidth() const {
  return scene_width_;
}

int RenderingEngine::GetSceneHeight() const {
  return scene_height_;
}

void RenderingEngine::Draw(double fov, map::Map &map, double facing_direction, position::Position position) {
  double ray_step = fov / GetSceneWidth();
  double angle = facing_direction - (fov / 2);

  for (int current_column = GetSceneWidth(); current_column > 0; --current_column) {
    angle = geometry::dmod(angle + ray_step, geometry::k359_degree);
    DrawColumn(current_column, angle, GetSceneHeight(), map, position, facing_direction);
  }
}

void RenderingEngine::DrawColumn(int column,
                                 double angle,
                                 int columns_height,
                                 map::Map &map,
                                 position::Position position,
                                 double facing_direction) {
  position::Position
      horizontal_intersection = geometry::findHorizontalWallIntersection(position, angle, map);
  position::Position vertical_intersection = geometry::findVerticalWallIntersection(position, angle, map);

  double horizontal_distance = geometry::findDistance(horizontal_intersection, position);
  double vertical_distance = geometry::findDistance(vertical_intersection, position);

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
      rendering_engine::RenderingEngine::GetTexture(0), //TODO chose how to select textures dinamically
      light_intensity,
      texture_column);

  double beta = std::abs(angle - facing_direction);
  DrawFloor(column, beta, columns_height, height, angle, position);
  DrawCeiling(column, columns_height, height);
}

void RenderingEngine::DrawFloor(int current_column,
                                double beta,
                                int columns_height,
                                double height,
                                double angle,
                                position::Position position) {
  double straight_line_distance, real_distance, light_intensity;
  double x_texture, y_texture;
  for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
    straight_line_distance =
        GetDistanceFromProjectionPlane() * GetCameraHeight()
            / (current_row - (static_cast<double>(columns_height) / 2.)); // TODO extract this function
    real_distance = straight_line_distance / cos(beta);
    light_intensity = GetLightIntensity(real_distance);

    y_texture = straight_line_distance * sin(angle) + position.y;
    x_texture = straight_line_distance * cos(angle) - position.x;

    color::ColorRGB
        color = rendering_engine::RenderingEngine::GetTexture(1).getColor(geometry::mod(x_texture, map::kBlockSize),
                                                                          geometry::mod(y_texture, map::kBlockSize));

    SetColor(current_column, current_row, color, light_intensity);
  }
}

void RenderingEngine::DrawCeiling(int current_column, int columns_height, double height) {
  for (int current_row = (int) ((columns_height + height) / 2.); current_row < GetSceneHeight(); ++current_row) {
    SetColor(current_column, current_row, color::kBlack);
  }
}

double RenderingEngine::GetDistanceFromProjectionPlane() const {
  return distance_from_projection_plane_;
}

double RenderingEngine::GetCameraHeight() const {
  return camera_height_;
}

double RenderingEngine::GetHeightConstant() const {
  return height_constant_;
}

int MapToTileSize(double coordinate, double range_size, double tile_size) {
  return static_cast<int>(coordinate / range_size * --tile_size);
}
}
