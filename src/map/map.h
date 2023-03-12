//
// Created by Stefano on 3/4/2023.
//

#ifndef ISRA_SRC_MAP_MAP_H_
#define ISRA_SRC_MAP_MAP_H_

#include <vector>

namespace map {

const static double kBlockSize = 64;
const static int kMapWidth = 5;
const static int kMapHeight = 8;

typedef std::vector<std::vector<int>> tMap;

class Map {

  tMap map_{};

 public:
  Map(tMap map);
  std::size_t getWidth();
  std::size_t getHeight();
  bool isWall(int x, int y);
};
}
#endif //ISRA_SRC_MAP_MAP_H_
