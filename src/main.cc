#include "main.h"

int main() {
  camera::Camera camera(960, 600, 60.0);

  camera.loadTexture("assets/wall.ppm");
  camera.loadTexture("assets/walkstone.ppm");

  window::Window main_window("Isra", &camera);
  map::Map map = map::Map::getCoolMap();

  main_window.mainLoop(&camera, map);
  exit(EXIT_SUCCESS);
}