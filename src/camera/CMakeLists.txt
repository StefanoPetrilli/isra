add_library(camera
        camera.cc camera.h)

target_link_libraries(camera PUBLIC position geometry map color texture)
target_include_directories(camera PUBLIC .)
