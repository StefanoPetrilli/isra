//
// Created by Stefano on 3/4/2023.
//

#include "map.h"

namespace map {
tMap Map::getMap() {
  return map_;
}

int Map::getWidth() {
  return kMapWidth;
}

int Map::getHeight() {
  return kMapHeight;
}

bool Map::isWall(int x, int y) {
  return map_.at(y).at(x);
}

}
