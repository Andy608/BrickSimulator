#pragma once
#ifndef BOUNTIVE_WINDOWFOCUSCALLBACK_H_
#define BOUNTIVE_WINDOWFOCUSCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class Logger;

	class WindowFocusCallback
	{
	public:
		static WindowFocusCallback* instance;

		static WindowFocusCallback* init();
		static void windowFocusCallback(GLFWwindow* windowHandle, GLint isFocused);

		~WindowFocusCallback();

	private:
		static Logger logger;
		WindowFocusCallback();
	};
}

#endif