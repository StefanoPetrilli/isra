add_subdirectory(camera)
add_subdirectory(map)
add_subdirectory(draw)
add_subdirectory(geometry)
add_subdirectory(window)

add_executable(isra main.cc main.h)
target_link_libraries(isra PUBLIC camera map draw geometry window ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLES2-lib})
