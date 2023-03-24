add_library(color
        color.h)

set_target_properties(color PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(color PUBLIC .)
