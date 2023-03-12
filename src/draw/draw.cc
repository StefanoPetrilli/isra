//
// Created by Stefano on 3/4/2023.
//

#include "draw.h"

namespace draw {
void draw(int columns_number, int columns_height, camera::Camera *camera, SDL_Renderer *renderer, map::Map map) {
  double ray_step = camera::Camera::getFOV() / columns_number,
      angle = camera->getFacingDirection() - (camera::Camera::getFOV() / 2),
      horizontal_distance, vertical_distance, height;

  camera::Position horizontal_intersection{}, vertical_intersection{};

  for (int current_column = columns_number; current_column > 0; angle += ray_step, --current_column) {

    horizontal_intersection = findHorizontalIntersection(camera->getPosition(), angle, map);
    vertical_intersection = findVerticalIntersection(camera->getPosition(), angle, map);

    horizontal_distance = findDistance(horizontal_intersection, camera->getPosition());
    vertical_distance = findDistance(vertical_intersection, camera->getPosition());

    auto min = horizontal_distance < vertical_distance ? horizontal_distance : vertical_distance;
    height = kHeightConstant / min;
    SDL_RenderDrawLine(renderer, current_column, ((columns_height / 2) + height / 2 ), current_column, ((columns_height / 2) - height / 2 ));
  }
}

void clean(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

camera::Position findFirstHorizontalIntersection(camera::Position camera_position, double angle, float tg) {
  camera::Position result{};

  result.y = floor(camera_position.y / map::kBlockSize) * map::kBlockSize + (isUp(angle) ? -1.0f : 64.0f);
  result.x = camera_position.x + (camera_position.y - result.y) / tg;

  return result;
}

camera::Position findHorizontalIntersection(camera::Position camera_position, double angle, map::Map map) {
  float tg = tan(angle * (3.1418 / 180.0));

  auto gridIntersection = findFirstHorizontalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.y += map::kBlockSize * (isUp(angle) ? -1 : 1);
    gridIntersection.x += map::kBlockSize / tg;
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

double isUp(double angle) {
  return angle < 180;
}

camera::Position findFirstVerticalIntersection(camera::Position camera_position, double angle, float tg) {
  camera::Position result{};

  result.x = (floor(camera_position.x / map::kBlockSize) * map::kBlockSize) + (isLeft(angle) ? -1 : map::kBlockSize);
  result.y = camera_position.y + ((camera_position.x - result.x) * tg);

  return result;
}

camera::Position findVerticalIntersection(camera::Position camera_position, double angle, map::Map map) {
  float tg = tan(angle * (3.1418 / 180.0));

  auto gridIntersection = findFirstVerticalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.x += map::kBlockSize * (isLeft(angle) ? -1 : 1);
    gridIntersection.y -= map::kBlockSize * tg;
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

bool isLeft(double angle) {
  return (angle > 90.0f && angle < 270.0f);
}

bool isInside(camera::Position position) {
  double x = mapToMap(position.x), y = mapToMap(position.y);
  return (x >= 0 && y >= 0) && (x < map::Map::getWidth() && y < map::Map::getHeight());
}

bool isWall(camera::Position position, map::Map map) {
  double x = mapToMap(position.x), y = mapToMap(position.y);
  return map.isWall(x, y);
}

int mapToMap(double x) {
  return floor(x / map::kBlockSize);
}

double findDistance(camera::Position intersection_position, camera::Position camera_position) {
  return sqrt(
      pow(intersection_position.x - camera_position.x, 2) + pow(intersection_position.y - camera_position.y, 2));
}
}
