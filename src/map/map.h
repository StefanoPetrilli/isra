//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_MAP_MAP_H_
#define ISRA_SRC_MAP_MAP_H_

#include <array>

namespace map {

const static double kBlockSize = 64;
const static int kMapWidth = 5;
const static int kMapHeight = 8;

typedef std::array<std::array<int, kMapWidth>, kMapHeight> tMap;


class Map {

  constexpr const static tMap map_{{
                                             {{0, 0, 1, 1}},
                                             {{0, 0, 0, 1}},
                                             {{0, 0, 0, 0}},
                                             {{0, 0, 0, 0}},
                                             {{0, 0, 0, 0}},
                                             {{0, 0, 0, 0}}
                                   }};

 public:
  static tMap getMap();
  static int getWidth();
  static int getHeight();
  static bool isWall(int x, int y);

};
}
#endif //ISRA_SRC_MAP_MAP_H_
