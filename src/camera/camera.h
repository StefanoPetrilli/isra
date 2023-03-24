//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_PLAYER_CAMERA_H_
#define ISRA_SRC_PLAYER_CAMERA_H_
#include <geometry.h>
#include <map.h>
#include <position.h>
#include <color.h>

#include <array>
#include <iostream>
#include <cmath>
#include <vector>
#include <GLFW/glfw3.h>

#define MOVE_CONSTANT 1
#define ROTATE_CONSTANT 0.01745329252f

namespace camera {
const static int kWindow_Width = 900;
const static int kWindow_Height = 600;
const static double kHeightConstant = map::kBlockSize * (camera::kWindow_Width / 2.0f) / 1.732050f;
constexpr static const double kDistanceFromProjectionPlane_ =
    (camera::kWindow_Width / 2.0f) / 1.732050f; //TODO lockup table for tan(kFOV_*3.14159/180);

class Camera {
  position::Position position_{};
  double view_direction_in_radians_;
  double height_;
  constexpr static const double kFOV_ = 1.0471975512;
  std::vector<unsigned char> pixels_;

 public:
  Camera();
  void move(int key);
  double getFacingDirectionInRadians() const;
  static double getFOVInRadians();
  position::Position getPosition();
  double getHeight() const;
  std::vector<unsigned char> &GetPixels();
  void FlushPixels();
  void draw(int columns_number,
            int columns_height,
            camera::Camera *camera,
            std::vector<unsigned char> &pixels,
            map::Map &map);

 private:
  void moveForward();
  void moveBackward();
  void moveRight();
  void moveLeft();
  void rotateLeft();
  void rotateRight();
  static void setColorLine(std::vector<unsigned char> &pixels, int column, int bottom, int top, color::ColorRGB color);
  static void setColor(int column, int row, std::vector<unsigned char> &pixels, color::ColorRGB color);
  static void drawColumn(int column,
                         double angle,
                         int height,
                         Camera *p_camera,
                         std::vector<unsigned char> &pixels,
                         map::Map &map);
  static void drawFloor(int current_column,
                        double beta,
                        int columns_height,
                        double height,
                        Camera *camera,
                        std::vector<unsigned char> &pixels);
  static void drawCeiling(int current_column,
                          double beta,
                          int columns_height,
                          double height,
                          Camera *camera,
                          std::vector<unsigned char> &pixels);
};

}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
