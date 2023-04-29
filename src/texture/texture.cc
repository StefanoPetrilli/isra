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
  int r, g, b;
  std::istringstream stream;
  while (std::getline(file, buffer)) {
    stream = std::istringstream(buffer);
    while (stream >> r && stream >> g && stream >> b)
      data_.push_back(color::ColorRGB{static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b)});
  }
}

texture::Texture::Texture(const char *file_name) {
  LoadTexture(file_name);
}

int texture::Texture::GetSize() {
  return size_;
}

int texture::Texture::GetChannels() {
  return channels_;
}

int Texture::GetWidth() {
  return width_;
}

int Texture::GetHeight() {
  return height_;
}

std::vector<color::ColorRGB> Texture::GetData() const {
  return data_;
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

color::ColorRGB Texture::GetColor(int x, int y) const {
  return data_[y * GetWidth() + x];
}
}
