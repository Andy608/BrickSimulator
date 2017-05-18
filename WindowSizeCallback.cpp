#include <iostream>
#include "WindowSizeCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	WindowSizeCallback* WindowSizeCallback::instance = nullptr;
	Logger WindowSizeCallback::logger = Logger("WindowSizeCallback", Logger::Level::LEVEL_ALL);

	WindowSizeCallback* WindowSizeCallback::init(GameSettingsHandler& gameSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new WindowSizeCallback(gameSettingsHandler);
		}

		return instance;
	}


	WindowSizeCallback::WindowSizeCallback(GameSettingsHandler& gameSettingsHandler) :
		mGameSettingsHandler(gameSettingsHandler)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating WindowSizeCallback...");
	}


	WindowSizeCallback::~WindowSizeCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting WindowSizeCallback...");
	}


	void WindowSizeCallback::windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		if (Window::instance->mMAXIMUM_SIZE_X == windowWidth
			&& Window::instance->mMAXIMUM_SIZE_Y - (Window::instance->mMAXIMUM_SIZE_Y / 8) < windowHeight)
		{
			instance->mGameSettingsHandler.setWindowMaximized(GL_TRUE);
			instance->mGameSettingsHandler.setDefaultWindowState();
		}
		else
		{
			instance->mGameSettingsHandler.setWindowMaximized(GL_FALSE);
			instance->mGameSettingsHandler.setWindowSizeX(windowWidth);
			instance->mGameSettingsHandler.setWindowSizeY(windowHeight);
		}
	}
}