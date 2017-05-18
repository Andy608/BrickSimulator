#pragma once
#ifndef BOUNTIVE_CURSORPOSITIONCALLBACK_H_
#define BOUNTIVE_CURSORPOSITIONCALLBACK_H_	

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class Logger;

	class CursorPositionCallback
	{
	public:
		static CursorPositionCallback* instance;

		static CursorPositionCallback* init();
		static void cursorPositionCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition);

		~CursorPositionCallback();

	private:
		static Logger logger;
		CursorPositionCallback();
	};
}

#endif