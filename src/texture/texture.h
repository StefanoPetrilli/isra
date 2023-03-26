//
// Created by Stefano on 3/26/2023.
//

#ifndef ISRA_SRC_TEXTURE_TEXTURE_H_
#define ISRA_SRC_TEXTURE_TEXTURE_H_

#include <iostream>
#include <fstream>

#include <color.h>
#include <vector>

namespace texture {

class Texture {
 public:
  explicit Texture(const char *file_name);
  ~Texture() = default;

  std::vector<unsigned char> getData() { return data_; }
  int width() const;
  int height() const;
  int channels() const;
  int size() const;
  color::ColorRGB getColor(int x, int y) const;

 private:
  void loadTexture(const char *file_name);
  static void IsRightEncoding(const std::string &encoding);
  static void IsValidFile(const std::ifstream &file);
  static void IsRightDimension(const std::string &dimensions_string);
  static void IsRightMaxValue(const std::string &max_value_string);
  void ReadPPMContent(std::ifstream &file);
  static void IsReadSuccessfull(const std::string &value);
  std::vector<unsigned char> data_;
  int width_ = 64;
  int height_ = 64;
  int channels_ = 3;
  int size_ = width_ * height_ * channels_;
};

}

#endif //ISRA_SRC_TEXTURE_TEXTURE_H_
