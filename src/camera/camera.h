//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_PLAYER_CAMERA_H_
#define ISRA_SRC_PLAYER_CAMERA_H_

#define MOVE_CONSTANT 1
#define ROTATE_CONSTANT 1
#define Q_KEY_PRESSED 113
#define W_KEY_PRESSED 119
#define E_KEY_PRESSED 101
#define A_KEY_PRESSED 97
#define S_KEY_PRESSED 115
#define D_KEY_PRESSED 100

namespace camera {

struct Position {
  float x;
  float y;
};

class Camera {
  Position position_{};
  float view_direction_;
  int height_;
  float FOV_;

 public:
  Camera();
  void move(int key);
  float getFacingDirection() const;
  float getFOV() const;
  Position getPosition();

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
