add_subdirectory(camera)
add_subdirectory(map)
add_subdirectory(draw)
add_subdirectory(radians)

add_executable(isra main.cc main.h)
target_link_libraries(isra PUBLIC ${SDL2_LIBRARIES} camera map draw radians)
