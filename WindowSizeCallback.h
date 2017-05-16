#pragma once
#ifndef BOUNTIVE_WINDOWSIZECALLBACK_H_
#define BOUNTIVE_WINDOWSIZECALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
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
		GameSettingsHandler& mGameSettingsHandler;

		WindowSizeCallback(GameSettingsHandler& gameSettingsHandler);
	};
}

#endif