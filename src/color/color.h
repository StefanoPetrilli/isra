//
// Created by Stefano on 3/24/2023.
//

#ifndef ISRA_SRC_COLOR_COLOR_H_
#define ISRA_SRC_COLOR_COLOR_H_
namespace color {
typedef struct ColorRGB {
  unsigned char r, g, b;

 ColorRGB operator*(const unsigned short x) const {
   return ColorRGB{static_cast<unsigned char>(r * x >> 16),
                   static_cast<unsigned char>(g * x >> 16),
                   static_cast<unsigned char>(b * x >> 16)};
 }
} ColorRGB;

const static ColorRGB kRed {255, 0, 0};
const static ColorRGB kGreen {0, 255, 0};
const static ColorRGB kBlue {0, 0, 255};
const static ColorRGB kBlack {0, 0, 0};

}
#endif //ISRA_SRC_COLOR_COLOR_H_
