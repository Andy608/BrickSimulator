#include <iostream>
#include "WindowSizeCallback.h"

namespace Bountive
{
	WindowSizeCallback* WindowSizeCallback::instance = nullptr;

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

	}


	WindowSizeCallback::~WindowSizeCallback()
	{
		std::cout << "Deleting WindowSizeCallback." << std::endl;
	}


	void WindowSizeCallback::windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		instance->mGameSettingsHandler.setWindowSizeX(windowWidth);
		instance->mGameSettingsHandler.setWindowSizeY(windowHeight);
	}
}