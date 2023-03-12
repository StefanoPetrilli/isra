//
// Created by Stefano on 3/12/2023.
//
#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <camera.h>
#include <draw.h>
#include <map.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(FindHorizontalIntersection, Expect_FirstHoriontalWallIntersection) {

  map::Map map({{1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}});

  camera::Position expected = {187, 63};
  auto result = draw::findHorizontalIntersection({96, 224}, 60, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(FindFirstHorizontalIntersection, Expect_FirstHorizontalIntersection) {

  map::Map map({{1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}});

  camera::Position expected = {115, 191};
  auto result = draw::findFirstHorizontalIntersection({96, 224}, 60, tan(60 * (3.1418 / 180.0)));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(FindVerticalIntersection, Expect_FirstVerticalWallIntersection) {

  map::Map map({{1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}});

  camera::Position expected = {192, 57.92f};
  auto result = draw::findVerticalIntersection({96, 224}, 60, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(FindFirstVerticalIntersection, Expect_FirstVerticalIntersection) {

  map::Map map({{1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}});

  camera::Position expected = {128, 168.64};
  auto result = draw::findFirstVerticalIntersection({96, 224}, 60, tan(60 * (3.1418 / 180.0)));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}