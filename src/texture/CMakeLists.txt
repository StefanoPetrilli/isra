add_library(texture
        texture.cc texture.h)

target_link_libraries(texture PUBLIC color)
target_include_directories(texture PUBLIC .)
