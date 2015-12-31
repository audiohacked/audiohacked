#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>

// #if defined (__APPLE_CC__)
// #include <OpenGL/gl3.h>
// #else
// #include <GL/gl3.h>       /* assert OpenGL 3.2 core profile available. */
// #endif

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// #define GLFW_INCLUDE_GL3  /* don't drag in legacy GL headers. */
// #define GLFW_NO_GLU       /* don't drag in the old GLU lib - unless you must. */
#include <GLFW/glfw3.h>

#include "error.hpp"
#include "hook.hpp"
#include "keyboard.hpp"
#include "overlay.hpp"
#include "render.hpp"
#include "text.hpp"
#include "settings.hpp"
