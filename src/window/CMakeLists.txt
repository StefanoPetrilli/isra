add_library(window
        window.cc window.h)

target_link_libraries(window PUBLIC map camera position)
target_include_directories(window PUBLIC .)
