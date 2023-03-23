//
// Created by Stefano on 3/13/2023.
//

#ifndef ISRA_SRC_RADIANS_RADIANS_H_
#define ISRA_SRC_RADIANS_RADIANS_H_
#include <position.h>
#include <map.h>

#include <array>
#include <iostream>
#include <cmath>

namespace geometry {
const double k60_degree = 1.0471975512f;
const double k90_degree = 1.5707963268f;
const double k120_degree = 2.0943951024f;
const double k180_degree = 3.1415926536f;
const double k270_degree = 4.7123889804f;
const double k300_degree = 5.235987756f;
const double k330_degree = 5.759586531f;

int mapToMap(double x);
bool isInside(position::Position position, map::Map map_1);
bool isWall(position::Position position, map::Map map);
position::Position findFirstHorizontalIntersection(position::Position camera_position, double angle, double tg);
position::Position findHorizontalWallIntersection(position::Position camera_position,
                                                  double angle,
                                                  const map::Map &map);
position::Position findFirstVerticalIntersection(position::Position camera_position, double angle, double tg);
position::Position findVerticalWallIntersection(position::Position camera_position, double angle, const map::Map &map);
double findDistance(position::Position intersection_position, position::Position camera_position);
bool isLeft(double angle);
bool isUp(double angle);
}
#endif //ISRA_SRC_RADIANS_RADIANS_H_
