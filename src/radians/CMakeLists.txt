add_library(radians
        radians.h)

set_target_properties(radians PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(radians PUBLIC .)
