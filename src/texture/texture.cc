//
// Created by Stefano on 3/26/2023.
//

#include "texture.h"
#include <iostream>
#include <string>
#include <sstream>

namespace texture {

void texture::Texture::loadTexture(const char *file_name) {

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
    stream = std::istringstream (buffer);
    while (stream >> number)
      data_.push_back(number);
  }
}

texture::Texture::Texture(char *file_name) {
  loadTexture(file_name);
}

int texture::Texture::size() const {
  { return size_; }
}

int texture::Texture::channels() const {
  { return channels_; }
}

int Texture::width() const {
  return width_;
}

int Texture::height() const {
  return height_;
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

}
