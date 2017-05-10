#pragma once
#ifndef BOUNTIVE_WINDOWPOSITIONCALLBACK_H_
#define BOUNTIVE_WINDOWPOSITIONCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class WindowPositionCallback
	{
	public:
		static WindowPositionCallback* instance;

		static WindowPositionCallback* init();
		static void windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition);

		~WindowPositionCallback();

	private:
		WindowPositionCallback();
	};
}

#endif