//
// Created by Stefano on 3/12/2023.
//
#include <gtest/gtest.h>
#include <map.h>
#include <geometry.h>
#include <texture.h>
#include <rendering_engine.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(findHorizontalWallIntersection_Forward, Expect_FirstHoriontalWallIntersection_Forward) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {187, 63};
  auto result = geometry::findHorizontalWallIntersection({96, 224}, geometry::k60_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstHorizontalIntersection_Forward, Expect_FirstHorizontalIntersection_Forward) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {115, 191};
  auto result = geometry::findFirstHorizontalIntersection({96, 224}, geometry::k60_degree, tan(geometry::k60_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findHorizontalWallIntersection_Back, Expect_FirstHoriontalWallIntersection_Back) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {151, 320};
  auto result = geometry::findHorizontalWallIntersection({96, 224}, geometry::k300_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstHorizontalIntersection_Back, Expect_FirstHorizontalIntersection_Back) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {115, 256};
  auto result = geometry::findFirstHorizontalIntersection({96, 224}, geometry::k300_degree, tan(geometry::k300_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findVerticalWallIntersection_Right, Expect_FirstVerticalWallIntersection_Right) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {192, 57.92f};
  auto result = geometry::findVerticalWallIntersection({96, 224}, geometry::k60_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstVerticalIntersection_Right, Expect_FirstVerticalIntersection_Right) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {128, 168.64};
  auto result = geometry::findFirstVerticalIntersection({96, 224}, geometry::k60_degree, tan(geometry::k60_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(findVerticalWallIntersection_Left, Expect_FirstVerticalWallIntersection_Left) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {64, 58};
  auto result = geometry::findVerticalWallIntersection({160, 224}, geometry::k120_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findVerticalWallIntersection, Expect_RightWallIntersection) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {192, 150};
  auto result = geometry::findVerticalWallIntersection({96, 96}, geometry::k330_degree, map);

  EXPECT_NEAR(expected.x, result.x, 3);
  EXPECT_NEAR(expected.y, result.y, 3);
}

TEST(findFirstVerticalIntersection_Left, Expect_FirstVerticalIntersection_Left) {

  map::Map map = map::Map::GetBasicMap();

  position::Position expected = {64, 166};
  auto result = geometry::findFirstVerticalIntersection({96, 224}, geometry::k120_degree, tan(geometry::k120_degree));

  EXPECT_NEAR(expected.x, result.x, 1);
  EXPECT_NEAR(expected.y, result.y, 1);
}

TEST(Texture, Expect_Constructor_ToLoadTexture) {

  const char *image_path = "assets/test_all_black.ppm";
  auto texture = texture::Texture(image_path);

  auto result = texture.GetData();
  std::vector<unsigned char> expected(64 * 64 * 3, 0);

  EXPECT_EQ(expected, result);
}

TEST(Texture, When_WrongFileName_Expect_Exception) {

  const char *image_path = "assets/test_all_black_no_file.ppm";

  EXPECT_THROW(auto texture = texture::Texture(image_path), std::invalid_argument);
}

TEST(Texture, When_WrongEncoding_Expect_Exception) {

  const char *image_path = "assets/test_all_black_wrong_encoding.ppm";

  EXPECT_THROW(auto texture = texture::Texture(image_path), std::invalid_argument);
}

TEST(Texture, When_WrongDimension_Expect_Exception) {

  const char *image_path = "assets/test_all_black_wrong_dimension.ppm";

  EXPECT_THROW(auto texture = texture::Texture(image_path), std::invalid_argument);
}

TEST(Texture, When_WrongMaxValue_Expect_Exception) {

  const char *image_path = "assets/test_all_black_wrong_max_value.ppm";

  EXPECT_THROW(auto texture = texture::Texture(image_path), std::invalid_argument);
}

TEST(MapToTileSize, When_Coordinate_IsEqualTo_RangeSize_Return_TileSizeMinus1) {
  auto coordinate = 64;
  auto range_size = 64;
  auto tile_size = 64;
  auto result = rendering_engine::MapToTileSize(coordinate, range_size, tile_size);
  auto expected = tile_size - 1;
  EXPECT_EQ(expected, result);
}

TEST(MapToTileSize, When_Coordinate_IsEqualTo_0_Return_0) {
  auto coordinate = 0;
  auto range_size = 64;
  auto tile_size = 64;
  auto result = rendering_engine::MapToTileSize(coordinate, range_size, tile_size);
  auto expected = 0;
  EXPECT_EQ(expected, result);
}
