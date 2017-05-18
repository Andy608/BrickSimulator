#pragma once
#ifndef BOUNTIVE_WINDOWSIZECALLBACK_H_
#define BOUNTIVE_WINDOWSIZECALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include <log4cxx\logger.h>
#include "GameSettingsHandler.h"

namespace Bountive
{
	class WindowSizeCallback
	{
	public:
		static WindowSizeCallback* instance;

		static WindowSizeCallback* init(GameSettingsHandler& gameSettingsHandler);
		static void windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight);

		~WindowSizeCallback();

	private:
		static Logger logger;
		GameSettingsHandler& mGameSettingsHandler;

		WindowSizeCallback(GameSettingsHandler& gameSettingsHandler);
	};
}

#endif