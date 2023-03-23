//
// Created by Stefano on 3/23/2023.
//

#include <geometry.h>

namespace geometry {

position::Position findFirstHorizontalIntersection(position::Position camera_position, double angle, double tg) {
  position::Position result{};

  result.y = floor(camera_position.y / map::kBlockSize) * map::kBlockSize + (geometry::isUp(angle) ? -1.0f : 64.0f);
  result.x = camera_position.x + (camera_position.y - result.y) / tg;

  return result;
}

position::Position findHorizontalWallIntersection(position::Position camera_position,
                                                  double angle,
                                                  const map::Map &map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstHorizontalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection, map)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.y += map::kBlockSize * (geometry::isUp(angle) ? -1 : 1);
    gridIntersection.x += map::kBlockSize / tg * (geometry::isUp(angle) ? 1 : -1);
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

position::Position findFirstVerticalIntersection(position::Position camera_position, double angle, double tg) {
  position::Position result{};

  result.x =
      (floor(camera_position.x / map::kBlockSize) * map::kBlockSize) + (geometry::isLeft(angle) ? -1 : map::kBlockSize);
  result.y = camera_position.y + ((camera_position.x - result.x) * tg);

  return result;
}

position::Position findVerticalWallIntersection(position::Position camera_position, double angle, const map::Map &map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstVerticalIntersection(camera_position, angle, tg);

  while (isInside(gridIntersection, map)) {
    if (isWall(gridIntersection, map)) {
      return gridIntersection;
    }

    gridIntersection.x += map::kBlockSize * (geometry::isLeft(angle) ? -1 : 1);
    gridIntersection.y += map::kBlockSize * tg * (geometry::isLeft(angle) ? 1 : -1);
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

bool isInside(position::Position position, map::Map map) {
  double x = mapToMap(position.x), y = mapToMap(position.y);
  return (x >= 0.0f && y >= 0.0f) && (x < map.getWidth() && y < map.getHeight());
}

bool isWall(position::Position position, map::Map map) {
  double x = mapToMap(position.x), y = mapToMap(position.y);
  return map.isWall(x, y);
}

int mapToMap(double x) {
  return floor(x / map::kBlockSize);
}

double findDistance(position::Position intersection_position, position::Position camera_position) {
  return sqrt(
      pow(intersection_position.x - camera_position.x, 2) + pow(intersection_position.y - camera_position.y, 2));
}

bool isLeft(double angle) {
  return (angle > k90_degree && angle < k270_degree);
}

bool isUp(double angle) {
  return angle < k180_degree;
}

}
