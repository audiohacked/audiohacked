#include "main.hpp"

int main(void)
{
	GLFWwindow* window;
	GLFWmonitor *monitor = NULL;
	const char* titleWindow = "Simple example";
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA

#if defined(OGL4)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	window = glfwCreateWindow(WIDTH, HEIGHT, titleWindow, monitor, NULL);
	// window = glfwCreateWindow(1920, 1080, "Simple example", glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	init_font();

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW not ok!" << std::endl;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// double start = glfwGetTime();
		fps = calcFPS(0.2);
		render(window);
		glfwSwapBuffers(window);
		glFinish();
		// fps = 1/(glfwGetTime()-start);
	}

	cleanup_font();
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
