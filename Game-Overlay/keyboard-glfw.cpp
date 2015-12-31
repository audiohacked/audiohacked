#include <GLFW/glfw3.h>

#include "settings.hpp"
#include "keyboard.hpp"

#define FPS_KEY (GLFW_KEY_F)
#define FPS_MOD 0//(GLFW_MOD_SHIFT|GLFW_MOD_ALT)
#define CLOCK_KEY (GLFW_KEY_T)
#define CLOCK_MOD 0//(GLFW_MOD_SHIFT|GLFW_MOD_ALT)
#define FORMAT_KEY (GLFW_KEY_M)
#define FORMAT_MOD (0)
#define QUIT_KEY (GLFW_KEY_ESCAPE)
#define QUIT_MOD (0)
#define OVERLAY_KEY (GLFW_KEY_TAB)
#define OVERLAY_MOD (GLFW_MOD_SHIFT|GLFW_MOD_ALT)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == QUIT_KEY && mods == QUIT_MOD && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == FPS_KEY && mods == FPS_MOD && action == GLFW_PRESS) {
		show_fps = !show_fps;
	}

	if (key == CLOCK_KEY && mods == CLOCK_MOD && action == GLFW_PRESS) {
		show_clock = !show_clock;
	}

	if (key == OVERLAY_KEY && mods == OVERLAY_MOD && action == GLFW_PRESS) {
		show_overlay = !show_overlay;
	}

	if (key == FORMAT_KEY && mods == FORMAT_MOD && action == GLFW_PRESS) {
		switch_format = !switch_format;
	}
}
