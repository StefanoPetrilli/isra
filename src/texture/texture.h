//
// Created by Stefano on 3/26/2023.
//

#ifndef ISRA_SRC_TEXTURE_TEXTURE_H_
#define ISRA_SRC_TEXTURE_TEXTURE_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <color.h>

namespace texture {

class Texture {
  void LoadTexture(const char *file_name);
  static void IsRightEncoding(const std::string &encoding);
  static void IsValidFile(const std::ifstream &file);
  static void IsRightDimension(const std::string &dimensions_string);
  static void IsRightMaxValue(const std::string &max_value_string);
  void ReadPPMContent(std::ifstream &file);
  static void IsReadSuccessfull(const std::string &value);
  std::vector<color::ColorRGB> data_;
  static constexpr int width_ = 64;
  static constexpr int height_ = 64;
  static constexpr int channels_ = 3;
  static constexpr int size_ = width_ * height_ * channels_;

 public:
  explicit Texture(const char *file_name);
  ~Texture() = default;
  static int GetWidth() ;
  static int GetHeight() ;
  static int GetChannels() ;
  static int GetSize() ;
  std::vector<color::ColorRGB> GetData() const;
  color::ColorRGB GetColor(int x, int y) const;
};

}

#endif //ISRA_SRC_TEXTURE_TEXTURE_H_
