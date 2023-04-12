add_library(radians
        radians.cc radians.h)

target_link_libraries(radians PUBLIC geometry)
target_include_directories(radians PUBLIC .)
