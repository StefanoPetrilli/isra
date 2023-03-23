add_subdirectory(camera)
add_subdirectory(map)
add_subdirectory(geometry)
add_subdirectory(window)
add_subdirectory(position)

add_executable(isra main.cc main.h)
target_link_libraries(isra PUBLIC camera map geometry window position ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLES2-lib})
