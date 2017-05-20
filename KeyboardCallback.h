#pragma once
#ifndef BOUNTIVE_KEYBOARDCALLBACK_H_
#define BOUNTIVE_KEYBOARDCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include "Window.h"

namespace Bountive
{
	class Logger;
	class GameSettingsHandler;
	class InputTracker;

	class KeyboardCallback
	{
	public:
		static KeyboardCallback* instance;

		static KeyboardCallback* init(const Window& window, GameSettingsHandler& gameSettingsHandler);
		static void keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode);
		
		~KeyboardCallback();

	private:
		static Logger logger;

		GameSettingsHandler& mGameSettingsHandler;
		InputTracker& mInputTracker;

		KeyboardCallback(const Window& window, GameSettingsHandler& gameSettingsHandler);
	};
}

#endif