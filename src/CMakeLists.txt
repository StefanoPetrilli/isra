add_subdirectory(camera)
add_subdirectory(map)
add_subdirectory(draw)
add_subdirectory(radians)

set(GLAD_GL "gl.h")

add_executable(isra main.cc main.h ${GLAD_GL})
target_link_libraries(isra PUBLIC ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} camera map draw radians)
