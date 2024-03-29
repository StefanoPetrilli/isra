//
// Created by Stefano on 4/16/2023.
//

#ifndef ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
#define ISRA_SRC_RENDERER_RENDERING_ENGINE_H_

#include <color.h>
#include <texture.h>
#include <geometry.h>
#include <distance_shader.h>

#include <cstring>
#include <vector>
#include <cmath>

namespace rendering_engine {
class RenderingEngine {
  int scene_width_;
  int scene_height_;
  std::vector<color::ColorRGB> pixels_;
  static std::vector<texture::Texture> textures_;
  double distance_from_projection_plane_;
  double camera_height_;
  double height_constant_;
  double straight_line_distance_constant_;
  double fov_;
  double ray_step_;
  map::Map map_;
  distance_shader::DistanceShader distance_shader_;
  int GetSceneWidth() const;
  int GetSceneHeight() const;
  double GetRayStep() const;
  double GetFov() const;
  double GetStraightLineDistanceConstant() const;
  void DrawFloor(int current_column,
                 int columns_height,
                 double height,
                 double angle,
                 position::Position position);
  double GetHeightConstant() const;
  void DrawColumn(int column, double angle, int columns_height, position::Position position);
  void SetColor(int column, int row, color::ColorRGB color);
  void SetColor(int column, int row, color::ColorRGB color, unsigned short intensity);
  void SetColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    unsigned short intensity,
                    int texture_vertical_coordinate);

 public:
  RenderingEngine() : RenderingEngine(0, 0, 0, 0, map::Map::GetBasicMap()) {}
  std::vector<color::ColorRGB> &GetPixels();
  RenderingEngine(int scene_width, int scene_height, double camera_height, double fov, map::Map map);
  static void LoadTexture(const char *path);
  static texture::Texture &GetTexture(int index);
  void Draw(double facing_direction, position::Position position);
  void ParallelDraw(double facing_direction, position::Position position);
  map::Map &GetMap();
};
int MapToTileSize(double coordinate, double range_size, double tile_size);
}
#endif //ISRA_SRC_RENDERER_RENDERING_ENGINE_H_
