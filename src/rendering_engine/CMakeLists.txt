add_subdirectory(distance_shader)

add_library(rendering_engine
        rendering_engine.cc rendering_engine.h)

target_link_libraries(rendering_engine PUBLIC color texture geometry distance_shader)
target_include_directories(rendering_engine PUBLIC .)
