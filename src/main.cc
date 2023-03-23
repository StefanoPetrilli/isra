#include "main.h"

int main() {
  camera::Camera camera;
  window::Window main_window(900, 600, "Isra", &camera);
  map::Map map({{0, 0, 0, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 0, 0, 0}});

  main_window.mainLoop(&camera, map);
  exit(EXIT_SUCCESS);
}