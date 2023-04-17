//
// Created by Stefano on 3/12/2023.
//
#include <rendering_engine.h>

#include <gtest/gtest.h>
#include <chrono>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(True, ExpectTrue) {
  rendering_engine::RenderingEngine::LoadTexture("assets/test_all_black.ppm");
  rendering_engine::RenderingEngine::LoadTexture("assets/test_all_black.ppm");
  rendering_engine::RenderingEngine rendering_engine(3840, 2160, 60.);
  auto map = map::Map::GetCoolMap();
  auto start = std::chrono::steady_clock::now();
  rendering_engine.Draw(geometry::k60_degree, map, 0., position::Position{.x = 100., .y = 100.});
  auto end = std::chrono::steady_clock::now();

  std::cout << "Elapsed time in milliseconds: "
       << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
       << " ms" << std::endl;
}
