#include <iostream>
#include "WindowPositionCallback.h"

namespace Bountive
{
	WindowPositionCallback* WindowPositionCallback::instance = nullptr;

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
		
	}


	WindowPositionCallback::~WindowPositionCallback()
	{
		std::cout << "Deleting WindowPositionCallback." << std::endl;
	}


	void WindowPositionCallback::windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition)
	{
		instance->mGameSettingsHandler.setWindowPositionX(xPosition);
		instance->mGameSettingsHandler.setWindowPositionY(yPosition);
	}
}