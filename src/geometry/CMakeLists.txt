add_library(geometry
        geometry.h)

set_target_properties(geometry PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(geometry PUBLIC .)
