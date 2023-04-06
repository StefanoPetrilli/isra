//
// Created by Stefano on 3/26/2023.
//

#include "texture.h"
#include <iostream>
#include <string>
#include <sstream>

namespace texture {

void texture::Texture::LoadTexture(const char *file_name) {

  std::ifstream file(file_name, std::ios::binary);
  IsValidFile(file);

  std::string buffer;
  std::getline(file, buffer);
  IsRightEncoding(buffer);

  std::getline(file, buffer);
  IsRightDimension(buffer);

  std::getline(file, buffer);
  IsRightMaxValue(buffer);

  ReadPPMContent(file);
  IsReadSuccessfull(buffer);
}

void texture::Texture::ReadPPMContent(std::ifstream &file) {
  std::string buffer;
  int number;
  std::istringstream stream;
  while (std::getline(file, buffer)) {
    stream = std::istringstream(buffer);
    while (stream >> number)
      data_.push_back(number);
  }
}

texture::Texture::Texture(const char *file_name) {
  LoadTexture(file_name);
}

int texture::Texture::GetSize() const {
  { return size_; }
}

int texture::Texture::GetChannels() const {
  { return channels_; }
}

int Texture::GetWidth() const {
  return width_;
}

int Texture::GetHeight() const {
  return height_;
}

unsigned char Texture::GetData(size_t index) const {
  return data_.at(index);
}

void Texture::IsRightEncoding(const std::string &encoding) {
  if (encoding != "P3")
    throw std::invalid_argument("Wrong encoding, only P3 is supported");
}

void texture::Texture::IsValidFile(const std::ifstream &file) {
  if (!file)
    throw std::invalid_argument("Failed to open file");
}

void Texture::IsRightDimension(const std::string &dimensions_string) {
  if (dimensions_string != "64 64")
    throw std::invalid_argument("Wrong dimension, only 64x64 is supported");
}

void Texture::IsRightMaxValue(const std::string &max_value_string) {
  if (max_value_string != "255")
    throw std::invalid_argument("Wrong max value, only 255 is supported");
}

void Texture::IsReadSuccessfull(const std::string &value) {
  if (value.empty())
    throw std::invalid_argument("Failed to read file");
}

//TODO test this function
color::ColorRGB Texture::getColor(int x, int y) const {
  if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight()) {
    int index = (y * GetWidth() + x) * GetChannels();
    return {.r = GetData(index), .g = GetData(index + 1), .b = GetData(index + 2)};
  }
  throw std::invalid_argument("Wrong coordinates");
}
}
