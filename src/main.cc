#include "main.h"

int main() {
  rendering_engine::RenderingEngine::LoadTexture("assets/wall.ppm");
  rendering_engine::RenderingEngine::LoadTexture("assets/walkstone.ppm");

  map::Map map = map::Map::GetCoolMap();
  camera::Camera camera(960, 600, 60., map);

  window::Window main_window("Isra", &camera);

  main_window.MainLoop(&camera);
  exit(EXIT_SUCCESS);
}