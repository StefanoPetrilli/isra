//
// Created by Stefano on 4/18/2023.
//

#include "distance_shader.h"

namespace distance_shader {
distance_shader::DistanceShader::DistanceShader(unsigned int max_distance) {
  intensity_values_.reserve(max_distance);
  for (unsigned int i = 0; i < max_distance; ++i) {
    intensity_values_.push_back(std::min((GetLightSourceConstant() / std::pow(i, 2)), 1.));
  }
}

double distance_shader::DistanceShader::GetIntensity(unsigned int distance) {
  return intensity_values_.at(distance);
}

double DistanceShader::GetLightSourceConstant() {
  return light_source_constant_;
}
}
