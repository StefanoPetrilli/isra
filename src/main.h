//
// Created by Stefano on 3/5/2023.
//

#ifndef ISRA_SRC_MAIN_H_
#define ISRA_SRC_MAIN_H_
#include <cstdlib>
#include <SDL2/SDL.h>
#include <camera.h>
#include <map.h>
#include <draw.h>
#include <iostream>

void quit(SDL_Renderer *renderer, SDL_Window *window);
void redraw(camera::Camera *camera, map::tMap map, SDL_Renderer *renderer, int pressed_key);

#endif //ISRA_SRC_MAIN_H_
