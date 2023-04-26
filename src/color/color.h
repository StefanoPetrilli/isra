//
// Created by Stefano on 3/24/2023.
//

#ifndef ISRA_SRC_COLOR_COLOR_H_
#define ISRA_SRC_COLOR_COLOR_H_
namespace color {
typedef struct ColorRGB {
  unsigned char r, g, b;

 ColorRGB operator*(const unsigned short int x) const {
   ColorRGB result{};
   result.r = r * x >> 16;
   result.g = g * x >> 16;
   result.b = b * x >> 16;
   return result;
 }
} ColorRGB;

const static ColorRGB kRed {255, 0, 0};
const static ColorRGB kGreen {0, 255, 0};
const static ColorRGB kBlue {0, 0, 255};
const static ColorRGB kBlack {0, 0, 0};

}
#endif //ISRA_SRC_COLOR_COLOR_H_
