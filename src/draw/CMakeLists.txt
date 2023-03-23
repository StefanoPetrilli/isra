add_library(draw
        draw.cc draw.h)

target_link_libraries(draw PUBLIC camera map geometry)
target_include_directories(draw PUBLIC .)
