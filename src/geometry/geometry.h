//
// Created by Stefano on 3/13/2023.
//

#ifndef ISRA_SRC_GEOMETRY_GEOMETRY_H_
#define ISRA_SRC_GEOMETRY_GEOMETRY_H_
#include <position.h>
#include <map.h>

#include <array>
#include <iostream>
#include <cmath>

namespace geometry {
const double k1_degree = 0.0174533;
const double k30_degree = 0.5235987756;
const double k60_degree = 1.0471975512;
const double k90_degree = 1.5707963268;
const double k120_degree = 2.0943951024;
const double k180_degree = 3.1415926536;
const double k270_degree = 4.7123889804;
const double k300_degree = 5.235987756;
const double k330_degree = 5.759586531;
const double k359_degree =  6.28318531;

position::Position findFirstHorizontalIntersection(position::Position camera_position, double angle, double tg);
position::Position findHorizontalWallIntersection(position::Position camera_position,
                                                  double angle,
                                                  map::Map &map);
position::Position findFirstVerticalIntersection(position::Position camera_position, double angle, double tg);
position::Position findVerticalWallIntersection(position::Position camera_position, double angle, map::Map &map);
double findDistance(position::Position intersection_position, position::Position camera_position);
bool isLeft(double angle);
bool isUp(double angle);
double dmod(double a, double b);
}
#endif //ISRA_SRC_GEOMETRY_GEOMETRY_H_
