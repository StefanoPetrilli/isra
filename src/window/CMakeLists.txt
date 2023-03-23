add_library(window
        window.cc window.h)

target_link_libraries(window PUBLIC draw map camera position)
target_include_directories(window PUBLIC .)
