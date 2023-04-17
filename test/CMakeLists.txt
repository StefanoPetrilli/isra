add_subdirectory(assets)

add_executable(isra_test
        main_test.cc)

add_executable(performance_test
        performance_test.cc)

target_link_libraries(isra_test
        PUBLIC
        GTest::gtest_main
        position
        camera
        map
        geometry
        texture
        color
        rendering_engine
        )

target_link_libraries(performance_test
        PUBLIC
        GTest::gtest_main
        rendering_engine
        )

include(GoogleTest)
gtest_discover_tests(isra_test)
gtest_discover_tests(performance_test)
