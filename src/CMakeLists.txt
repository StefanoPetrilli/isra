add_subdirectory(assets)
add_subdirectory(camera)
add_subdirectory(color)
add_subdirectory(distance_shader)
add_subdirectory(geometry)
add_subdirectory(map)
add_subdirectory(position)
add_subdirectory(rendering_engine)
add_subdirectory(texture)
add_subdirectory(window)

add_executable(isra main.cc main.h)
target_link_libraries(isra PUBLIC camera map window texture ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLES2-lib})
