add_library(draw
        draw.cc draw.h)

target_link_libraries(draw PUBLIC ${SDL2_LIBRARIES} camera map radians)
target_include_directories(draw PUBLIC .)
