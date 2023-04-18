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
#include <rendering_engine.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <GLFW/glfw3.h>

namespace camera {
class Camera {
  position::Position position_{};
  double view_direction_in_radians_;
  int scene_height_;
  int scene_width_;
  const double kFOV_ = geometry::k60_degree;
  double rotation_step_ = geometry::k1_degree;
  double move_step_ = 1.;
  rendering_engine::RenderingEngine engine_;
  void MoveForward();
  void MoveBackward();
  void MoveRight();
  void MoveLeft();
  void RotateLeft();
  void RotateRight();

 public:
  Camera(int scene_width, int scene_height, double camera_height, map::Map &map);
  void Move(int key);
  double GetFacingDirectionInRadians() const;
  double GetFovInRadians() const;
  position::Position GetPosition();
  int GetSceneWidth() const;
  int GetSceneHeight() const;
  double GetRotationStep() const;
  double GetMoveStep() const;
  std::vector<unsigned char> &GetPixels();
  void Draw();
};
}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
