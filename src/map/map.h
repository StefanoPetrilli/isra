//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_MAP_MAP_H_
#define ISRA_SRC_MAP_MAP_H_

#include <position.h>

#include <vector>
#include <utility>
#include <cmath>

namespace map {

typedef std::vector<std::vector<int>> tMap;

const static double kBlockSize = 64.;
const static tMap kCoolMap = {{1, 1, 1, 1, 1, 1},
                              {1, 0, 0, 0, 0, 1},
                              {1, 0, 1, 1, 1, 1},
                              {1, 0, 0, 0, 0, 1},
                              {1, 0, 1, 1, 1, 1},
                              {1, 0, 0, 0, 0, 1},
                              {1, 0, 0, 0, 1, 1},
                              {1, 0, 0, 0, 0, 1},
                              {1, 0, 0, 0, 0, 1},
                              {1, 1, 1, 1, 1, 1}};

const static tMap kBasicMap = {{1, 1, 1, 1},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {1, 1, 1, 1}};

class Map {

  explicit Map(tMap map);
  tMap map_{};

 public:
  static Map GetCoolMap();
  static Map GetBasicMap();
  std::size_t GetWidth();
  std::size_t GetHeight();
  bool IsWall(int x, int y);
  static int MapToMap(double x);
  bool IsInside(position::Position position);
  bool IsWall(position::Position position);
};
}
#endif //ISRA_SRC_MAP_MAP_H_
