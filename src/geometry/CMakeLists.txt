add_library(geometry
        geometry.cc geometry.h)

target_link_libraries(geometry PUBLIC map position)
target_include_directories(geometry PUBLIC .)
