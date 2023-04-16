//
// Created by Stefano on 4/16/2023.
//

#ifndef ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
#define ISRA_SRC_RENDERER_RENDERING_ENGINE_H_

#include <color.h>
#include <texture.h>

#include <vector>

namespace rendering_engine {
class RenderingEngine {
  int width_;
  int height_;
  std::vector<unsigned char> pixels_;

 public:
  RenderingEngine() : RenderingEngine(0, 0) {}
  std::vector<unsigned char> &GetPixels();
  RenderingEngine(int width, int height);
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  void SetColor(int column, int row, color::ColorRGB color);
  void SetColor(int column, int row, color::ColorRGB color, double intensity);
  void SetColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    double intensity,
                    int texture_vertical_coordinate);
};
int MapToTileSize(double coordinate, double range_size, double tile_size);
}
#endif //ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
