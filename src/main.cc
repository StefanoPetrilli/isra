#include "main.h"

int main() {
  GLuint texture;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  camera::Camera camera;
  map::Map map({{0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 0, 0, 0}});

  GLFWwindow *window = glfwCreateWindow(camera::kWindow_Width, camera::kWindow_Height, "Isra", nullptr, nullptr);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  gladLoadGL(glfwGetProcAddress);

  std::vector<unsigned char> pixels(camera::kWindow_Width * camera::kWindow_Height * 3, 0);
  //std::fill_n(pixels, camera::kWindow_Width * camera::kWindow_Height, 0);

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
               pixels.data());
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  0,
                  0,
                  camera::kWindow_Width,
                  camera::kWindow_Height,
                  GL_RGB,
                  GL_UNSIGNED_BYTE,
                  pixels.data());

  GLuint readFboId = 0;
  glGenFramebuffers(1, &readFboId);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
  glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, texture, 0);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

  while (!glfwWindowShouldClose(window)) {
    redraw(&camera, map, pixels);

    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    camera::kWindow_Width,
                    camera::kWindow_Height,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    pixels.data());

    glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    glBlitFramebuffer(0, 0, camera::kWindow_Width,
                      camera::kWindow_Height,
                      0, 0, camera::kWindow_Width,
                      camera::kWindow_Height,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glfwSwapBuffers(window);

    glfwWaitEvents();
  }

  glfwPollEvents();
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void redraw(camera::Camera *camera, map::Map map, std::vector<unsigned char> &pixels) {
  std::cout << camera->getPosition().x << "; " << camera->getPosition().y << " - "
            << camera->getFacingDirectionInRadians()
            << std::endl;
  draw::draw(camera::kWindow_Width, camera::kWindow_Height, camera, pixels, map);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  switch (key) {
    case (GLFW_KEY_ESCAPE): glfwSetWindowShouldClose(window, GLFW_TRUE);
      //case (GLFW_KEY_W): redraw(&camera, map, renderer, event.key.keysym.sym);
      //  break;
  }
}

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}
