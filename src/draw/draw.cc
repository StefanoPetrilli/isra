//
// Created by Stefano on 3/4/2023.
//

#include "draw.h"

namespace draw {
void draw(int columns_number, int columns_height, camera::Camera *camera, SDL_Renderer *renderer, const map::Map& map) {
  double ray_step = camera::Camera::getFOVInRadians() / columns_number,
      angle = camera->getFacingDirectionInRadians() - (camera::Camera::getFOVInRadians() / 2),
      horizontal_distance, vertical_distance, height;

  camera::Position horizontal_intersection{}, vertical_intersection{};

  for (int current_column = columns_number; current_column > 0; angle += ray_step, --current_column) {

    horizontal_intersection = findHorizontalWallIntersection(camera->getPosition(), angle, map);
    vertical_intersection = findVerticalWallIntersection(camera->getPosition(), angle, map);

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

camera::Position findFirstHorizontalIntersection(camera::Position camera_position, double angle, double tg) {
  camera::Position result{};

  result.y = floor(camera_position.y / map::kBlockSize) * map::kBlockSize + (isUp(angle) ? -1.0f : 64.0f);
  result.x = camera_position.x + (camera_position.y - result.y) / tg;

  return result;
}

camera::Position findHorizontalWallIntersection(camera::Position camera_position, double angle, const map::Map& map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstHorizontalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection, map)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.y += map::kBlockSize * (isUp(angle) ? -1 : 1);
    gridIntersection.x += map::kBlockSize / tg * (isUp(angle) ? 1 : -1);
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

camera::Position findFirstVerticalIntersection(camera::Position camera_position, double angle, double tg) {
  camera::Position result{};

  result.x = (floor(camera_position.x / map::kBlockSize) * map::kBlockSize) + (isLeft(angle) ? -1 : map::kBlockSize);
  result.y = camera_position.y + ((camera_position.x - result.x) * tg);

  return result;
}

camera::Position findVerticalWallIntersection(camera::Position camera_position, double angle, const map::Map& map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstVerticalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection, map)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.x += map::kBlockSize * (isLeft(angle) ? -1 : 1);
    gridIntersection.y += map::kBlockSize * tg * (isLeft(angle) ? 1 : -1);
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

bool isInside(camera::Position position, map::Map map) {
  double x = mapToMap(position.x), y = mapToMap(position.y);
  return (x >= 0.0f && y >= 0.0f) && (x < map.getWidth() && y < map.getHeight());
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

bool isLeft(double angle) {
  return (angle > radians::k90_degree && angle < radians::k270_degree);
}

bool isUp(double angle) {
  return angle < radians::k180_degree;
}
}
