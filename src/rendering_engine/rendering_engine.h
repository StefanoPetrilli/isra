//
// Created by Stefano on 4/16/2023.
//

#ifndef ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
#define ISRA_SRC_RENDERER_RENDERING_ENGINE_H_

#include <color.h>
#include <texture.h>
#include <geometry.h>

#include <vector>
#include <cmath>

namespace rendering_engine {
class RenderingEngine {
  int scene_width_;
  int scene_height_;
  std::vector<unsigned char> pixels_;
  static std::vector<texture::Texture> textures_;
  double distance_from_projection_plane_;
  double camera_height_;
  double height_constant_;
  double GetLightSourceConstant() const;
  double GetLightIntensity(double distance) const;
  int GetSceneWidth() const;
  int GetSceneHeight() const;
  double GetDistanceFromProjectionPlane() const;
  double GetCameraHeight() const;
  void DrawCeiling(int current_column, int columns_height, double height);
  void DrawFloor(int current_column,
                 double beta,
                 int columns_height,
                 double height,
                 double angle,
                 position::Position position);
  double GetHeightConstant() const;
  void DrawColumn(int column,
                  double angle,
                  int columns_height,
                  map::Map &map,
                  position::Position position,
                  double facing_direction);
  void SetColor(int column, int row, color::ColorRGB color);
  void SetColor(int column, int row, color::ColorRGB color, double intensity);
  void SetColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    double intensity,
                    int texture_vertical_coordinate);

 public:
  RenderingEngine() : RenderingEngine(0, 0, 0) {}
  std::vector<unsigned char> &GetPixels();
  RenderingEngine(int scene_width, int scene_height, double camera_height);
  static void LoadTexture(const char *path);
  static texture::Texture GetTexture(int index);
  void Draw(int columns_number,
            int columns_height,
            double fov,
            map::Map &map,
            double facing_direction,
            position::Position position);
};
int MapToTileSize(double coordinate, double range_size, double tile_size);
}
#endif //ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
