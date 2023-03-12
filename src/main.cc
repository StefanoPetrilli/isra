#include "main.h"

int main() {
  SDL_Event event;
  SDL_Renderer *renderer;
  SDL_Window *window;

  camera::Camera camera;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(camera::kWindow_Width, camera::kWindow_Height, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  map::Map map;

  draw::draw(camera::kWindow_Width, camera::kWindow_Height, &camera, renderer, map);
  SDL_RenderPresent(renderer);

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

void redraw(camera::Camera *camera, map::Map map, SDL_Renderer *renderer, int pressed_key) {
  camera->move(pressed_key);
  std::cout << camera->getPosition().x << "; " << camera->getPosition().y << " - " << camera->getFacingDirection() << std::endl;
  draw::clean(renderer);
  draw::draw(camera::kWindow_Width, camera::kWindow_Height, camera, renderer, map);
  SDL_RenderPresent(renderer);
}

void quit(SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
