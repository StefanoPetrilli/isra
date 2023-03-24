//
// Created by Stefano on 3/4/2023.
//

#include "map.h"

namespace map {

std::size_t Map::getWidth() {
  return map_.at(0).size();
}

std::size_t Map::getHeight() {
  return map_.size();
}

bool Map::isWall(int x, int y) {
  return map_.at(y).at(x);
}

Map::Map(tMap map) {
  map_ = std::move(map);
}

int Map::mapToMap(double x) {
  return floor(x / map::kBlockSize);
}

bool Map::isWall(position::Position position) {
  double x = this->mapToMap(position.x), y = this->mapToMap(position.y);
  return this->isWall(x, y);
}

bool Map::isInside(position::Position position) {
  double x = this->mapToMap(position.x), y = this->mapToMap(position.y);
  return (x >= 0.0f && y >= 0.0f) && (x < this->getWidth() && y < this->getHeight());
}

Map Map::getCoolMap() {
  return Map(kCoolMap);
}

Map Map::getBasicMap() {
  return Map(kBasicMap);
}

}
