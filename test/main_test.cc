//
// Created by Stefano on 3/12/2023.
//
#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <camera.h>
#include <draw.h>
#include <map.h>
#include <radians.h>

const map::tMap kBaseMap = {{1, 1, 1, 1},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {1, 1, 1, 1}};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(findHorizontalWallIntersection_Forward, Expect_FirstHoriontalWallIntersection_Forward) {

  map::Map map(kBaseMap);

  camera::Position expected = {187, 63};
  auto result = draw::findHorizontalWallIntersection({96, 224}, radians::k60_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstHorizontalIntersection_Forward, Expect_FirstHorizontalIntersection_Forward) {

  map::Map map(kBaseMap);

  camera::Position expected = {115, 191};
  auto result = draw::findFirstHorizontalIntersection({96, 224}, radians::k60_degree, tan(radians::k60_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findHorizontalWallIntersection_Back, Expect_FirstHoriontalWallIntersection_Back) {

  map::Map map(kBaseMap);

  camera::Position expected = {151, 320};
  auto result = draw::findHorizontalWallIntersection({96, 224}, radians::k300_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstHorizontalIntersection_Back, Expect_FirstHorizontalIntersection_Back) {

  map::Map map(kBaseMap);

  camera::Position expected = {115, 256};
  auto result = draw::findFirstHorizontalIntersection({96, 224}, radians::k300_degree, tan(radians::k300_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findVerticalWallIntersection_Right, Expect_FirstVerticalWallIntersection_Right) {

  map::Map map(kBaseMap);

  camera::Position expected = {192, 57.92f};
  auto result = draw::findVerticalWallIntersection({96, 224}, radians::k60_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstVerticalIntersection_Right, Expect_FirstVerticalIntersection_Right) {

  map::Map map(kBaseMap);

  camera::Position expected = {128, 168.64};
  auto result = draw::findFirstVerticalIntersection({96, 224}, radians::k60_degree, tan(radians::k60_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findVerticalWallIntersection_Left, Expect_FirstVerticalWallIntersection_Left) {

  map::Map map(kBaseMap);

  camera::Position expected = {64, 58};
  auto result = draw::findVerticalWallIntersection({160, 224}, radians::k120_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstVerticalIntersection_Left, Expect_FirstVerticalIntersection_Left) {

  map::Map map(kBaseMap);

  camera::Position expected = {64, 166};
  auto result = draw::findFirstVerticalIntersection({96, 224}, radians::k120_degree, tan(radians::k120_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}