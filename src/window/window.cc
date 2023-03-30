//
// Created by Stefano on 3/20/2023.
//

#include "window.h"
#include "camera.h"

namespace window {
Window::Window(int width,
               int height,
               const std::string &window_name,
               camera::Camera *camera) {

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  window_ = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
  if (!window_) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetKeyCallback(window_, key_callback);

  glfwMakeContextCurrent(window_);
  glfwSetWindowUserPointer(window_, camera);
  glfwSwapInterval(1);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  srand((unsigned int) glfwGetTimerValue());

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               camera::kWindow_Width,
               camera::kWindow_Height,
               0,
               GL_RGB,
               GL_UNSIGNED_BYTE,
               camera->GetPixels().data());
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  0,
                  0,
                  camera::kWindow_Width,
                  camera::kWindow_Height,
                  GL_RGB,
                  GL_UNSIGNED_BYTE,
                  camera->GetPixels().data());

  glGenFramebuffers(1, &readFboId_);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId_);
  glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, texture, 0);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

}

void Window::mainLoop(camera::Camera *camera, map::Map &map) {
  while (!glfwWindowShouldClose(window_)) {
    std::cout << camera->getPosition().x << "; " << camera->getPosition().y << " - "
              << camera->getFacingDirectionInRadians()
              << std::endl;

    camera->draw(camera::kWindow_Width, camera::kWindow_Height, map);

    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    camera::kWindow_Width,
                    camera::kWindow_Height,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    camera->GetPixels().data());

    glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId_);
    glBlitFramebuffer(0, 0, camera::kWindow_Width,
                      camera::kWindow_Height,
                      0, 0, camera::kWindow_Width,
                      camera::kWindow_Height,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glfwSwapBuffers(window_);

    glfwWaitEvents();
  }

  glfwPollEvents();
  glfwTerminate();
}

void Window::error_callback(int error, const char *description) {
  std::cerr << "Error " << error << ": " << description << std::endl;
}

void Window::key_callback(GLFWwindow *window,
                          int key,
                          [[maybe_unused]] int scancode,
                          [[maybe_unused]] int action,
                          [[maybe_unused]] int mods) {
  key == GLFW_KEY_ESCAPE ? glfwSetWindowShouldClose(window, GLFW_TRUE) : ((camera::Camera *) glfwGetWindowUserPointer(
      window))->move(key);
}
}
