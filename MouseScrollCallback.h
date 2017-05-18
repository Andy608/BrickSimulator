#pragma once
#ifndef BOUNTIVE_MOUSESCROLLCALLBACK_H_
#define BOUNTIVE_MOUSESCROLLCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class Logger;

	class MouseScrollCallback
	{
	public:
		static MouseScrollCallback* instance;

		static MouseScrollCallback* init();
		static void mouseScrollCallback(GLFWwindow* windowHandle, GLdouble xOffset, GLdouble yOffset);

		~MouseScrollCallback();

	private:
		static Logger logger;
		MouseScrollCallback();
	};
}

#endif