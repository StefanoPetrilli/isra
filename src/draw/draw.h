//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_DRAW_H_
#define ISRA_SRC_DRAW_H_

#include <cmath>
#include <iostream>
#include <array>

#include <map.h>
#include <camera.h>
#include <geometry.h>
#include <position.h>

namespace draw {

const static double kHeightConstant = map::kBlockSize * camera::Camera::GetDistanceFromProjectionPlane();

void draw(int columns_number,
          int columns_height,
          camera::Camera *camera,
          std::vector<unsigned char> &pixels,
          const map::Map &map);
bool isWall(position::Position position, map::Map map);
position::Position findHorizontalWallIntersection(position::Position camera_position, double angle, const map::Map &map);
position::Position findVerticalWallIntersection(position::Position camera_position, double angle, const map::Map &map);
position::Position findFirstHorizontalIntersection(position::Position camera_position, double angle, double tg);
position::Position findFirstVerticalIntersection(position::Position camera_position, double angle, double tg);
int mapToMap(double x);
bool isInside(position::Position position, map::Map map_1);
double findDistance(position::Position intersection_position, position::Position camera_position);
bool isLeft(double angle);
bool isUp(double angle);
void setColor(int column,
              int row,
              std::vector<unsigned char> &pixels,
              unsigned char r,
              unsigned char g,
              unsigned char b);
void setColorLine(std::vector<unsigned char> &vector,
                  int column,
                  int bottom,
                  int top,
                  unsigned char r,
                  unsigned char g,
                  unsigned char b);
void flush_pixels(std::vector<unsigned char> &vector);
}
#endif //ISRA_SRC_DRAW_H_
