#include "main.h"

int main() {
  camera::Camera camera(960, 600, 60.);

  camera.LoadTexture("assets/wall.ppm");
  camera.LoadTexture("assets/walkstone.ppm");

  window::Window main_window("Isra", &camera);
  map::Map map = map::Map::GetCoolMap();

  main_window.MainLoop(&camera, map);
  exit(EXIT_SUCCESS);
}