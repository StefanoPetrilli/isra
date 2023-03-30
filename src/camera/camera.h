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

#define MOVE_CONSTANT 1
#define ROTATE_CONSTANT 0.01745329252f

namespace camera {
const static int kWindow_Width = 900;
const static int kWindow_Height = 600;
const static double kLight_Source_Constant = 2500;
const static double kHeightConstant = map::kBlockSize * (camera::kWindow_Width / 2.0f) / 1.732050f;
constexpr static const double kDistanceFromProjectionPlane_ =
    (camera::kWindow_Width / 2.0f) / 1.732050f; //TODO lockup table for tan(kFOV_*3.14159/180);

class Camera {
  position::Position position_{};
  double view_direction_in_radians_;
  double height_;
  const double kFOV_ = geometry::k60_degree;
  std::vector<unsigned char> pixels_;
  std::vector<texture::Texture> textures_;

 public:
  Camera();
  void move(int key);
  double getFacingDirectionInRadians() const;
  double getFOVInRadians();
  position::Position getPosition();
  double getHeight() const;
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
  double getLightIntensity(double distance);
  void setColor(int column, int row, color::ColorRGB color, double intensity);
  void setColorLine(int column,
                    int bottom,
                    int top,
                    const texture::Texture &texture,
                    double intensity,
                    int texture_vertical_coordinate);
};

int MapToTileSize(double coordinate, double range_size, double tile_size);
int mod(double a, double b);
}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
