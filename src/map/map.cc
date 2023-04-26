//
// Created by Stefano on 3/4/2023.
//

#include "map.h"

namespace map {

std::size_t Map::GetWidth() {
  return map_[0].size();
}

std::size_t Map::GetHeight() {
  return map_.size();
}

bool Map::IsWall(int x, int y) {
  return map_[y][x];
}

Map::Map(tMap map) {
  map_ = std::move(map);
}

int Map::MapToMap(double x) {
  return floor(x / map::kBlockSize);
}

bool Map::IsWall(position::Position position) {
  double x = this->MapToMap(position.x), y = this->MapToMap(position.y);
  return this->IsWall(x, y);
}

bool Map::IsInside(position::Position position) {
  double x = MapToMap(position.x), y = MapToMap(position.y);
  return (x >= 0.0f && y >= 0.0f) && (x < GetWidth() && y < GetHeight());
}

Map Map::GetCoolMap() {
  return Map(kCoolMap);
}

Map Map::GetBasicMap() {
  return Map(kBasicMap);
}
}
