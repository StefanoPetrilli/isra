add_library(camera
        camera.cc camera.h)

target_link_libraries(camera PUBLIC position geometry map)
target_include_directories(camera PUBLIC .)
