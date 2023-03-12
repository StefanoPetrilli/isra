add_executable(isra_test
        main_test.cc
        )

target_link_libraries(isra_test
        PUBLIC
        ${SDL2_LIBRARIES}
        GTest::gtest_main
        draw
        camera
        map)

include(GoogleTest)
gtest_discover_tests(isra_test)