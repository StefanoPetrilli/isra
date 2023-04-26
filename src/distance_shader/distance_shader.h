//
// Created by Stefano on 4/18/2023.
//
#include <vector>
#include <cmath>

#ifndef ISRA_SRC_DISTANCE_SHADER_DISTANCE_SHADER_H_
namespace distance_shader {
class DistanceShader {
  std::vector<double> intensity_values_;
  constexpr static double light_source_constant_ = 4000;

 public:
  DistanceShader() : DistanceShader(0) {};
  explicit DistanceShader(unsigned int max_distance);
  ~DistanceShader() = default;
  double GetIntensity(unsigned int distance);
  static double GetLightSourceConstant();
};
}
#define ISRA_SRC_DISTANCE_SHADER_DISTANCE_SHADER_H_

#endif //ISRA_SRC_DISTANCE_SHADER_DISTANCE_SHADER_H_
