//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_MAP_MAP_H_
#define ISRA_SRC_MAP_MAP_H_

#include <array>

namespace map {

typedef std::array<std::array<int, 4>, 4> tMap;

class Map {

  constexpr const static tMap map_{{
                                             {{1, 1, 1, 1}},
                                             {{0, 1, 0, 0}},
                                             {{0, 1, 0, 0}},
                                             {{0, 0, 0, 0}}
                                   }};

 public:
  static tMap getMap();

};
}
#endif //ISRA_SRC_MAP_MAP_H_
