//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_DRAW_H_
#define ISRA_SRC_DRAW_H_
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <map.h>
#include <camera.h>

namespace draw {
void draw(int columns_number, int columns_height, camera::Camera *camera, SDL_Renderer *renderer, map::tMap map);
void clean(SDL_Renderer *renderer);
bool isWall(camera::Position position, map::tMap map);
camera::Position findHorizontalIntersection(camera::Position camera_position, float angle, map::tMap map);
int mapToMap(float x);
bool isInside(camera::Position position, map::tMap map);
float findDistance(camera::Position intersection_position, camera::Position camera_position);
}
#endif //ISRA_SRC_DRAW_H_
