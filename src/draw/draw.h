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
#include <radians.h>

namespace draw {

const static double kHeightConstant = map::kBlockSize * camera::Camera::GetDistanceFromProjectionPlane();

void draw(int columns_number, int columns_height, camera::Camera *camera, SDL_Renderer *renderer, const map::Map& map);
void clean(SDL_Renderer *renderer);
bool isWall(camera::Position position, map::Map map);
camera::Position findHorizontalWallIntersection(camera::Position camera_position, double angle, const map::Map& map);
camera::Position findVerticalWallIntersection(camera::Position camera_position, double angle, const map::Map& map);
camera::Position findFirstHorizontalIntersection(camera::Position camera_position, double angle, double tg);
camera::Position findFirstVerticalIntersection(camera::Position camera_position, double angle, double tg);
int mapToMap(double x);
bool isInside(camera::Position position, map::Map map_1);
double findDistance(camera::Position intersection_position, camera::Position camera_position);
bool isLeft(double angle);
bool isUp(double angle);
}
#endif //ISRA_SRC_DRAW_H_
