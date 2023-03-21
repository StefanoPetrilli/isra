#include "main.h"

int main() {
  std::vector<unsigned char> pixels(camera::kWindow_Width * camera::kWindow_Height * 3, 0);
  camera::Camera camera;
  window::Window main_window(900, 600, "Isra", pixels, &camera);
  map::Map map({{0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 0, 0, 0}});

  main_window.mainLoop(pixels, &camera, map);
  exit(EXIT_SUCCESS);
}