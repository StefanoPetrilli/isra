add_library(camera
        camera.cc camera.h)

target_link_libraries(camera PUBLIC position)
target_include_directories(camera PUBLIC .)
