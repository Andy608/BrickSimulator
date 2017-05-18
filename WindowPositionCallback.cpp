#include <iostream>
#include "WindowPositionCallback.h"
#include "Logger.h"

namespace Bountive
{
	WindowPositionCallback* WindowPositionCallback::instance = nullptr;
	Logger WindowPositionCallback::logger = Logger("WindowPositionCallback", Logger::Level::LEVEL_ALL);

	WindowPositionCallback* WindowPositionCallback::init(GameSettingsHandler& gameSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new WindowPositionCallback(gameSettingsHandler);
		}

		return instance;
	}


	WindowPositionCallback::WindowPositionCallback(GameSettingsHandler& gameSettingsHandler) :
		mGameSettingsHandler(gameSettingsHandler)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating WindowPositionCallback...");
	}


	WindowPositionCallback::~WindowPositionCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting WindowPositionCallback...");
	}


	void WindowPositionCallback::windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition)
	{
		if (!instance->mGameSettingsHandler.isWindowMaximized().getCustomBoolean())
		{
			instance->mGameSettingsHandler.setWindowPositionX(xPosition);
			instance->mGameSettingsHandler.setWindowPositionY(yPosition);
		}
	}
}