//
// Created by Stefano on 4/12/2023.
//

#ifndef ISRA_SRC_RADIANS_RADIANS_H_
#define ISRA_SRC_RADIANS_RADIANS_H_

#include <cmath>
#include <geometry.h>

namespace radians {
class Radians {
  double value_;
  constexpr static double degree_to_radians_coefficient_ = M_PI_2 / 180.;

 public:
  Radians();
  explicit Radians(double radians_value);
  void Sum(double value);
  double GetValue() const;
};
}
#endif //ISRA_SRC_RADIANS_RADIANS_H_
