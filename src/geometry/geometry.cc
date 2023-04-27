//
// Created by Stefano on 3/23/2023.
//

#include <geometry.h>

namespace geometry {

position::Position findFirstHorizontalIntersection(position::Position camera_position, double angle, double tg) {
  position::Position result{};

  result.y = floor(camera_position.y / map::kBlockSize) * map::kBlockSize + (geometry::isUp(angle) ? -1.f : 64.f);
  result.x = camera_position.x + (camera_position.y - result.y) / tg;

  return result;
}

position::Position findHorizontalWallIntersection(position::Position camera_position,
                                                  double angle,
                                                  map::Map &map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstHorizontalIntersection(camera_position, angle, tg);

  while (map.IsInside(gridIntersection)) {
    if (map.IsWall(gridIntersection)) {
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

position::Position findVerticalWallIntersection(position::Position camera_position,
                                                double angle,
                                                map::Map &map) {
  double tg = tan(angle);

  auto gridIntersection = findFirstVerticalIntersection(camera_position, angle, tg);

  while (map.IsInside(gridIntersection)) {
    if (map.IsWall(gridIntersection)) {
      return gridIntersection;
    }

    gridIntersection.x += map::kBlockSize * (geometry::isLeft(angle) ? -1 : 1);
    gridIntersection.y += map::kBlockSize * tg * (geometry::isLeft(angle) ? 1 : -1);
  }

  return {.x = HUGE_VAL, .y = HUGE_VAL};
}

double findDistance(position::Position intersection_position, position::Position camera_position) {
  return sqrt(
      pow(intersection_position.x - camera_position.x, 2) + pow(intersection_position.y - camera_position.y, 2));
}

bool isLeft(double angle) {
  return (angle > k90_degree && angle <= k270_degree);
}

bool isUp(double angle) {
  return angle <= k180_degree;
}

int mod(double a, double b) {
  double result = std::fmod(a, b);
  if (result < 0) {
    result += b;
  }
  return static_cast<int>(result);
}

double dmod(double a, double b) {
  return std::fmod(a + b, b);
}
}
