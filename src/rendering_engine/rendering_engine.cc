//
// Created by Stefano on 4/16/2023.
//

#include "rendering_engine.h"

namespace rendering_engine {
std::vector<texture::Texture> RenderingEngine::textures_;

rendering_engine::RenderingEngine::RenderingEngine(int width, int height) {
  width_ = width;
  height_ = height;
  pixels_ = std::vector<unsigned char>(width * height * 3, 0);
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color, double intensity) {
  SetColor(column, row, color * intensity);
}

void RenderingEngine::SetColor(int column, int row, color::ColorRGB color) {
  auto index = (column + (row * GetWidth())) * 3;
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

texture::Texture RenderingEngine::GetTexture(int index) {
  return textures_[index];
}

double RenderingEngine::GetLightSourceConstant() const {
  return 4000.;
}

double RenderingEngine::GetLightIntensity(double distance) const {
  return std::min((GetLightSourceConstant() / std::pow(distance, 2)), 1.);
}

int MapToTileSize(double coordinate, double range_size, double tile_size) {
  return static_cast<int>(coordinate / range_size * --tile_size);
}
}
