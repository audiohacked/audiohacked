#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "error.hpp"

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

