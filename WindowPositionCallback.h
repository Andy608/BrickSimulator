#pragma once
#ifndef BOUNTIVE_WINDOWPOSITIONCALLBACK_H_
#define BOUNTIVE_WINDOWPOSITIONCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include "GameSettingsHandler.h"

namespace Bountive
{
	class GameSettingsHandler;

	class WindowPositionCallback
	{
	public:
		static WindowPositionCallback* instance;

		static WindowPositionCallback* init(GameSettingsHandler& gameSettingsHandler);
		static void windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition);

		~WindowPositionCallback();

	private:
		GameSettingsHandler& mGameSettingsHandler;

		WindowPositionCallback(GameSettingsHandler& gameSettingsHandler);
	};
}

#endif