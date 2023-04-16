add_library(rendering_engine
        rendering_engine.cc rendering_engine.h)

target_link_libraries(rendering_engine PUBLIC color texture)
target_include_directories(rendering_engine PUBLIC .)
