#include "WindowSizeCallback.h"
#include "GameSettingsHandler.h"
#include <iostream>

namespace Bountive
{
	WindowSizeCallback* WindowSizeCallback::instance = nullptr;

	WindowSizeCallback* WindowSizeCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new WindowSizeCallback();
		}

		return instance;
	}


	WindowSizeCallback::WindowSizeCallback() {}


	WindowSizeCallback::~WindowSizeCallback()
	{
		std::cout << "Deleting WindowSizeCallback." << std::endl;
	}


	void WindowSizeCallback::windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		GameSettingsHandler::instance->setWindowSizeX(windowWidth);
		GameSettingsHandler::instance->setWindowSizeY(windowHeight);
	}
}