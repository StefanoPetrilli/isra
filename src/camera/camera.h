//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_PLAYER_CAMERA_H_
#define ISRA_SRC_PLAYER_CAMERA_H_
#include <geometry.h>
#include <map.h>
#include <position.h>
#include <color.h>
#include <texture.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <GLFW/glfw3.h>

namespace camera {
class Camera {
  position::Position position_{};
  double view_direction_in_radians_;
  double camera_height_;
  int scene_height_;
  int scene_width_;
  const double kFOV_ = geometry::k60_degree;
  std::vector<unsigned char> pixels_;
  std::vector<texture::Texture> textures_;
  double height_constant_;
  double distance_from_projection_plane_;
  const double light_source_constant_ = 4000; //TODO
  double rotation_step_ = geometry::k1_degree;
  double move_step_ = 1.;
  void MoveForward();
  void MoveBackward();
  void MoveRight();
  void MoveLeft();
  void RotateLeft();
  void RotateRight();
  void SetColor(int column, int row, color::ColorRGB color);
  void DrawColumn(int column, double angle, int columns_height, map::Map &map);
  void DrawFloor(int current_column, double beta, int columns_height, double height, double angle);
  void DrawCeiling(int current_column, int columns_height, double height);
  double GetLightIntensity(double distance) const;
  void SetColor(int column, int row, color::ColorRGB color, double intensity);
  void SetColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    double intensity,
                    int texture_vertical_coordinate);

 public:
  Camera(int scene_width, int scene_height, double camera_height);
  void Move(int key);
  double GetFacingDirectionInRadians() const;
  double GetFovInRadians() const;
  position::Position GetPosition();
  double GetCameraHeight() const;
  int GetSceneWidth() const;
  int GetSceneHeight() const;
  double GetHeightConstant() const;
  double GetDistanceFromProjectionPlane() const;
  double GetLightSourceConstant() const;
  double GetRotationStep() const;
  double GetMoveStep() const;
  std::vector<unsigned char> &GetPixels();
  void Draw(int columns_number, int columns_height, map::Map &map);
  void LoadTexture(const char *path);
  texture::Texture GetTexture(int index);
};

int MapToTileSize(double coordinate, double range_size, double tile_size);
}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
