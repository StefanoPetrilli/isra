//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_PLAYER_CAMERA_H_
#define ISRA_SRC_PLAYER_CAMERA_H_

#define MOVE_CONSTANT 1
#define ROTATE_CONSTANT 0.01745329252f
#define Q_KEY_PRESSED 113
#define W_KEY_PRESSED 119
#define E_KEY_PRESSED 101
#define A_KEY_PRESSED 97
#define S_KEY_PRESSED 115
#define D_KEY_PRESSED 100

namespace camera {
const static int kWindow_Width = 900;
const static int kWindow_Height = 600;

struct Position {
  double x;
  double y;
};

class Camera {
  Position position_{};
  double view_direction_in_radians_;
  double height_;
  constexpr static const double kFOV_ = 1.0471975512;
  constexpr static const double kDistanceFromProjectionPlane_ = (camera::kWindow_Width / 2.0f) / 1.732050f; //TODO lockup table for tan(kFOV_*3.14159/180);

 public:
  Camera();
  void move(int key);
  double getFacingDirectionInRadians() const;
  static double getFOVInRadians();
  Position getPosition();
  static double GetDistanceFromProjectionPlane();

 protected:
  void moveForward();
  void moveBackward();
  void moveRight();
  void moveLeft();
  void rotateLeft();
  void rotateRight();
};

}
#endif //ISRA_SRC_PLAYER_CAMERA_H_
