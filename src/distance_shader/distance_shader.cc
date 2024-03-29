//
// Created by Stefano on 4/18/2023.
//

#include "distance_shader.h"

namespace distance_shader {
distance_shader::DistanceShader::DistanceShader(unsigned int max_distance) {
  intensity_values_.reserve(max_distance);

  for (unsigned int i = 0; i < max_distance; ++i) {
    intensity_values_.push_back(
        std::min(
            static_cast<int>(GetLightSourceConstant() / std::pow(i, 2) * 65535.),
            65535
        )
    ); //TODO is this std::min really needed?
  }
}

unsigned short distance_shader::DistanceShader::GetIntensity(unsigned int distance) const {
  return intensity_values_[distance];
}

double DistanceShader::GetLightSourceConstant() {
  return light_source_constant_;
}
}
