//
// Created by Stefano on 3/4/2023.
//

#include <array>
#include "draw.h"

namespace draw {
void draw(int columns_number,
          int columns_height,
          camera::Camera *camera,
          std::vector<unsigned char> &pixels,
          const map::Map &map) {
  double ray_step = camera::Camera::getFOVInRadians() / columns_number,
      angle = camera->getFacingDirectionInRadians() - (camera::Camera::getFOVInRadians() / 2),
      horizontal_distance, vertical_distance, height, straight_line_distance, real_distance, beta;
  int wall_bottom;

  camera::Position horizontal_intersection{}, vertical_intersection{};

  for (int current_column = columns_number; current_column > 0; angle += ray_step, --current_column) {

    horizontal_intersection = findHorizontalWallIntersection(camera->getPosition(), angle, map);
    vertical_intersection = findVerticalWallIntersection(camera->getPosition(), angle, map);

    horizontal_distance = findDistance(horizontal_intersection, camera->getPosition());
    vertical_distance = findDistance(vertical_intersection, camera->getPosition());

    auto min = horizontal_distance < vertical_distance ? horizontal_distance : vertical_distance;
    height = kHeightConstant / min;
    wall_bottom = floor((columns_height - height) / 2);
    setColorLine(pixels,
                 current_column,
                 (int) ((columns_height - height) / 2),
                 (int) ((columns_height + height) / 2),
                 255,
                 0,
                 0);
    beta = abs(angle - camera->getFacingDirectionInRadians());
    for (int current_row = (int) ((columns_height - height) / 2); current_row > 0; --current_row) {
      straight_line_distance =
          camera->getDistanceFromProjectionPlane() * camera->getHeight() / (current_row - (columns_height / 2));
      real_distance = straight_line_distance / cos(beta);
      setColor(current_column, current_row, pixels, 0, 255, 0);
    }
  }
}

void setColorLine(std::vector<unsigned char> &pixels,
                  int column,
                  int bottom,
                  int top,
                  unsigned char r,
                  unsigned char g,
                  unsigned char b) {
  for (int i = top; i > bottom; --i) {
    setColor(column, i, pixels, r, g, b);
  }
}

camera::Position findFirstHorizontalIntersection(camera::Position camera_position, double angle, double tg) {
  camera::Position result{};

  result.y = floor(camera_position.y / map::kBlockSize) * map::kBlockSize + (isUp(angle) ? -1.0f : 64.0f);
  result.x = camera_position.x + (camera_position.y - result.y) / tg;

  return result;
}

camera::Position findHorizontalWallIntersection(camera::Position camera_position, double angle, const map::Map &map) {
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

camera::Position findVerticalWallIntersection(camera::Position camera_position, double angle, const map::Map &map) {
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

void setColor(int column,
              int row,
              std::vector<unsigned char> &pixels,
              unsigned char r,
              unsigned char g,
              unsigned char b) {
  auto index = (column + (row * camera::kWindow_Width)) * 3;
  if (index > 1620000) return;
  pixels[index] = r;
  pixels[index + 1] = g;
  pixels[index + 2] = b;
}

void flush_pixels(std::vector<unsigned char> &vector) {
  std::fill(vector.begin(), vector.end(), 0);
}
}
