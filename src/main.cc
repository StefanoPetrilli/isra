#include "main.h"

int main() {
  camera::Camera camera;
  camera.LoadTexture("assets/wall.ppm");
  window::Window main_window(900, 600, "Isra", &camera);
  map::Map map = map::Map::getCoolMap();

  main_window.mainLoop(&camera, map);
  exit(EXIT_SUCCESS);
}