#include "main.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

int main() {
  SDL_Event event;
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  camera::Camera camera;
  map::tMap map = map::Map::getMap();

  draw::draw(WINDOW_WIDTH, WINDOW_HEIGHT, &camera, renderer, map);

  while (true) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case (SDL_QUIT):quit(renderer, window);
          return EXIT_SUCCESS;
        case (SDL_KEYDOWN):redraw(&camera, map, renderer, event.key.keysym.sym);
          break;
      }
    }
  }
}

void redraw(camera::Camera *camera, map::tMap map, SDL_Renderer *renderer, int pressed_key) {
  camera->move(pressed_key);
  std::cout << camera->getPosition().x << "; " << camera->getPosition().y << std::endl;
  draw::clean(renderer);
  draw::draw(WINDOW_WIDTH, WINDOW_HEIGHT, camera, renderer, map);
}

void quit(SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
