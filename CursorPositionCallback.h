#pragma once
#ifndef BOUNTIVE_CURSORPOSITIONCALLBACK_H_
#define BOUNTIVE_CURSORPOSITIONCALLBACK_H_	

#include <glew.h>
#include <glfw\glfw3.h>
#include <glm\vec2.hpp>

namespace Bountive
{
	class InputTracker;
	class Logger;

	class CursorPositionCallback
	{
	public:
		static CursorPositionCallback* instance;

		static CursorPositionCallback* init(InputTracker& INPUT_TRACKER);
		static void cursorPositionCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition);

		~CursorPositionCallback();

	private:
		static Logger logger;

		InputTracker& mInputTracker;
		
		CursorPositionCallback(InputTracker& INPUT_TRACKER);
	};
}

#endif