#pragma once
#ifndef BOUNTIVE_WINDOWPOSITIONCALLBACK_H_
#define BOUNTIVE_WINDOWPOSITIONCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include "FileSettingsHandler.h"

namespace Bountive
{
	class FileSettingsHandler;

	class WindowPositionCallback
	{
	public:
		static WindowPositionCallback* instance;

		static WindowPositionCallback* init(FileSettingsHandler& fileSettingsHandler);
		static void windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition);

		~WindowPositionCallback();

	private:
		static Logger logger;
		FileSettingsHandler& mFileSettingsHandler;

		WindowPositionCallback(FileSettingsHandler& fileSettingsHandler);
	};
}

#endif