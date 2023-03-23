add_library(position
        position.h)

set_target_properties(position PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(position PUBLIC .)
