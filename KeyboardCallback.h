#pragma once
#ifndef BOUNTIVE_KEYBOARDCALLBACK_H_
#define BOUNTIVE_KEYBOARDCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include "Window.h"

namespace Bountive
{
	class FileSettingsHandler;
	class InputTracker;
	class Logger;

	class KeyboardCallback
	{
	public:
		static KeyboardCallback* instance;

		static KeyboardCallback* init(InputTracker& INPUT_TRACKER, FileSettingsHandler& fileSettingsHandler);
		static void keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode);
		
		~KeyboardCallback();

	private:
		static Logger logger;

		FileSettingsHandler& mFileSettingsHandler;
		InputTracker& mInputTracker;

		KeyboardCallback(InputTracker& INPUT_TRACKER, FileSettingsHandler& fileSettingsHandler);
	};
}

#endif