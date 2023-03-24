//
// Created by Stefano on 3/24/2023.
//

#ifndef ISRA_SRC_COLOR_COLOR_H_
#define ISRA_SRC_COLOR_COLOR_H_
namespace color {
typedef struct ColorRGB {
  unsigned char r, g, b;
} ColorRGB;

const static ColorRGB kRed {255, 0, 0};
const static ColorRGB kGreen {0, 255, 0};
const static ColorRGB kBlue {0, 0, 255};

}
#endif //ISRA_SRC_COLOR_COLOR_H_
