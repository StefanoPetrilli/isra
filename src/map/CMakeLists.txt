add_library(map
        map.cc map.h)

target_link_libraries(map PUBLIC position)
target_include_directories(map PUBLIC .)
