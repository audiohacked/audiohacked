#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <GLFW/glfw3.h>

#include <FTGL/ftgl.h>

#include "text.hpp"
#include "overlay.hpp"
#include "settings.hpp"

double fps = 0;
bool show_fps = false;
bool show_clock = false;
bool show_overlay = false;
bool switch_format = true;

extern FTGL::FTGLfont *font;

double calcFPS(double theTimeInterval, std::string theWindowTitle)
{
	// Static values which only get initialised the first time the function runs
	static double t0Value       = glfwGetTime(); // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps           = 0.0;           // Set the initial FPS value to 0.0

	// Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1) {
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0) {
		theTimeInterval = 10.0;
	}

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// // If the user specified a window title to append the FPS value to...
		// if (theWindowTitle != "NONE")
		// {
		// 	// Convert the fps value into a string using an output stringstream
		// 	std::ostringstream stream;
		// 	stream << fps;
		// 	std::string fpsString = stream.str();
		//
		// 	// Append the FPS value to the window title details
		// 	theWindowTitle += " | FPS: " + fpsString;
		//
		// 	// Convert the new window title to a c_str and set it
		// 	const char* pszConstString = theWindowTitle.c_str();
		// 	// glfwSetWindowTitle(pszConstString);
		// }
		// else // If the user didn't specify a window to append the FPS to then output the FPS to the console
		// {
		// 	std::cout << "FPS: " << fps << std::endl;
		// }

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}

void view_upperleft(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Ortho(left, right, bottom, top, ...)
	glOrtho(0.f, 10.f, -10.f, 0.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void view_lowerleft(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 10.f, 0, 10.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void view_upperright(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10.f, 0.f, -10.f, 0.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void view_lowerright(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10.f, 0.f, 0.f, 10.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw_fps(GLFWwindow* window)
{
	if(!font) return;
	std::stringstream fps_string;
	fps_string << std::fixed << std::setprecision(2) << fps << " FPS";
	// fps_string << "\t" << std::fixed << std::setprecision(1) << fps << " FPS";
	// fps_string << "\t" << std::fixed << std::setprecision(0) << fps << " FPS";

	glColor3f(0.f, 1.f, 0.f);

	view_lowerleft(window);
	glRasterPos2f(0.f, 0.f);
	
	if (show_fps || show_overlay) {
		/* Set the font size and render a small text. */
		ftglSetFontFaceSize(font, 24, 24);
		ftglRenderFont(font, fps_string.str().c_str(), FTGL::RENDER_ALL);
	}
}

void draw_clock(GLFWwindow* window)
{
	if(!font) return;

	std::string FORMAT;
	if(switch_format) {
		FORMAT = "%T";
	} else {
		FORMAT = "%I:%M:%S %p";
	}

	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo;
	timeinfo = localtime(&rawtime);

	std::stringstream system_time_string;
	system_time_string << std::put_time(timeinfo, FORMAT.c_str());

	glColor3f(0.f, 1.f, 0.f);

	view_upperleft(window);
	glRasterPos2f(0.f, -0.2f);

	if (show_clock || show_overlay) {
		/* Set the font size and render a small text. */
		ftglSetFontFaceSize(font, 24, 24);
		ftglRenderFont(font, system_time_string.str().c_str(), FTGL::RENDER_ALL);
	}
}
