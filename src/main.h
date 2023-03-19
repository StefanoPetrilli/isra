//
// Created by Stefano on 3/5/2023.
//

#ifndef ISRA_SRC_MAIN_H_
#define ISRA_SRC_MAIN_H_
#include <cstdlib>
#include <SDL2/SDL.h>
#include <camera.h>
#include <map.h>
#include <draw.h>
#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include "gl.h"
//#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>

void redraw(camera::Camera *camera, map::Map map, std::vector<unsigned char> &pixels);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void error_callback(int error, const char *description);

typedef struct vec3 {
  float x, y, z;
} vec3;

#endif //ISRA_SRC_MAIN_H_
