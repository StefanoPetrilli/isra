cmake_minimum_required(VERSION 3.22)
project(isra)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR})
add_compile_options(-Wall -Wextra -Wpedantic)

# Include google test
include(FetchContent)
include(GoogleTest)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

#GLES2
find_library(GLES2-lib GLESv2)

add_subdirectory(src)
add_subdirectory(test)
