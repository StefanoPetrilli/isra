//
// Created by Stefano on 3/4/2023.
//

#include "draw.h"

namespace draw {
void draw(int columns_number, int columns_height, camera::Camera *camera, SDL_Renderer *renderer, map::tMap map) {
  float ray_step = camera->getFOV() / columns_number;
  float distance, height;
  camera::Position horizontal_intersection;
  for (float angle = camera->getFacingDirection() - (camera->getFOV() / 2), current_column = 0;
       current_column < columns_number; angle += ray_step, ++current_column) {
    horizontal_intersection = findHorizontalIntersection(camera->getPosition(), angle, map);

    if (horizontal_intersection.x == 9999)
      continue;

    distance = findDistance(horizontal_intersection, camera->getPosition());
    height = (64.0 / distance) * 250.0;

    for (int i = 0; i < height / 2; i++) {
      SDL_RenderDrawPoint(renderer, current_column, (columns_height / 2) + i);
      SDL_RenderDrawPoint(renderer, current_column, (columns_height / 2) - i);
    }
  }

  SDL_RenderPresent(renderer);
}

void clean(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

camera::Position findHorizontalIntersection(camera::Position camera_position, float angle, map::tMap map) {
  camera::Position gridIntersection = {};
  float tg = tan(angle * (3.1418 / 180.0));
  gridIntersection.y = (floor(camera_position.y / 64) * 64) - 1;
  gridIntersection.x = camera_position.x + ((camera_position.y - gridIntersection.y) / tg);

  while (isInside(gridIntersection, map)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }
    gridIntersection.x += (64 / tg);
    gridIntersection.y -= 64;
  }

  camera::Position nothingHit = {.x = 9999, .y = 9999};
  return nothingHit;
}
bool isInside(camera::Position position, map::tMap map) {
  float x = mapToMap(position.x), y = mapToMap(position.y);
  return (x >= 0 && y >= 0) && (x < 4 && y < 4);
}

bool isWall(camera::Position position, map::tMap map) {
  float x = mapToMap(position.x), y = mapToMap(position.y);
  return map.at(y).at(x);
}

int mapToMap(float x) {
  return floor(x / 64);
}

float findDistance(camera::Position intersection_position, camera::Position camera_position) {
  return sqrt(
      pow(intersection_position.x - camera_position.x, 2) + pow(intersection_position.y - camera_position.y, 2));
}
}
