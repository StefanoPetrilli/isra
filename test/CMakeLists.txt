add_executable(isra_test
        main_test.cc)

target_link_libraries(isra_test
        PUBLIC
        GTest::gtest_main
        position
        camera
        map
        geometry)

include(GoogleTest)
gtest_discover_tests(isra_test)