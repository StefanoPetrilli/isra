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
#include <draw.h>
#include <camera.h>

namespace window {
class Window {

 private:
  GLFWwindow *window_;
  GLuint readFboId_ = 0;
  static void error_callback(int error, const char *description);
  static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

 public:
  Window(int width,
         int height,
         const std::string &window_name,
         camera::Camera *camera);
  void mainLoop(camera::Camera *camera, const map::Map &map);
};
}

#endif //ISRA_SRC_WINDOW_WINDOW_H_
