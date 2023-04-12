//
// Created by Stefano on 4/12/2023.
//

#include "radians.h"

namespace radians {

Radians::Radians() : Radians(0.) {}

radians::Radians::Radians(double radians_value) {
  value_ = geometry::dmod(radians_value, geometry::k359_degree);
}

void radians::Radians::Sum(double value) {
  value_ = geometry::dmod(value_ + value, geometry::k359_degree);
}

double radians::Radians::GetValue() const {
  return value_;
}
}
