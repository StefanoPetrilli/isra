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

 public:
  Camera(int scene_width, int scene_height, double camera_height);
  void move(int key);
  double getFacingDirectionInRadians() const;
  double getFOVInRadians() const;
  position::Position getPosition();
  double getCameraHeight() const;
  int getSceneWidth() const;
  int getSceneHeight() const;
  double getHeightConstant() const;
  double getDistanceFromProjectionPlane() const;
  double getLightSourceConstant() const;
  double getRotationStep() const;
  double getMoveStep() const;
  std::vector<unsigned char> &GetPixels();
  void draw(int columns_number, int columns_height, map::Map &map);
  void loadTexture(const char *path);
  texture::Texture getTexture(int index);

 private:
  void moveForward();
  void moveBackward();
  void moveRight();
  void moveLeft();
  void rotateLeft();
  void rotateRight();
  void setColor(int column, int row, color::ColorRGB color);
  void drawColumn(int column, double angle, int height, map::Map &map);
  void drawFloor(int current_column, double beta, int columns_height, double height, double angle);
  void drawCeiling(int current_column, double beta, int columns_height, double height);
  double getLightIntensity(double distance) const;
  void setColor(int column, int row, color::ColorRGB color, double intensity);
  void setColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    double intensity,
                    int texture_vertical_coordinate);
};

int MapToTileSize(double coordinate, double range_size, double tile_size);
}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
