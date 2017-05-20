#include "WindowSizeCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	WindowSizeCallback* WindowSizeCallback::instance = nullptr;
	Logger WindowSizeCallback::logger = Logger("WindowSizeCallback", Logger::Level::LEVEL_ALL);

	WindowSizeCallback* WindowSizeCallback::init(const Window& window, GameSettingsHandler& gameSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new WindowSizeCallback(window, gameSettingsHandler);
		}

		return instance;
	}


	WindowSizeCallback::WindowSizeCallback(const Window& window, GameSettingsHandler& gameSettingsHandler) :
		mWindow(window),
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
		if (instance->mWindow.mMAXIMUM_SIZE_X == windowWidth
			&& instance->mWindow.mMAXIMUM_SIZE_Y - (instance->mWindow.mMAXIMUM_SIZE_Y / 8) < windowHeight)
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