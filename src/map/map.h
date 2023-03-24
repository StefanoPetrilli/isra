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

const static double kBlockSize = 64;
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

  tMap map_{};

 public:
  static Map getCoolMap();
  static Map getBasicMap();
  std::size_t getWidth();
  std::size_t getHeight();
  bool isWall(int x, int y);
  static int mapToMap(double x);
  bool isInside(position::Position position);
  bool isWall(position::Position position);

 private:
  explicit Map(tMap map);
};
}
#endif //ISRA_SRC_MAP_MAP_H_
