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

}
