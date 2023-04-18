//
// Created by Stefano on 3/20/2023.
//

#ifndef ISRA_SRC_WINDOW_WINDOW_H_
#define ISRA_SRC_WINDOW_WINDOW_H_

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <vector>
#include <camera.h>

namespace window {
class Window {

  GLFWwindow *window_;
  GLuint readFboId_ = 0;
  static void error_callback(int error, const char *description);
  static void key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, int mods);

 public:
  Window(const std::string &window_name, camera::Camera *camera);
  void MainLoop(camera::Camera *camera);
};
}

#endif //ISRA_SRC_WINDOW_WINDOW_H_
