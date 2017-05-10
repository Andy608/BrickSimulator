#include "WindowSizeCallback.h"
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
		//TODO: Set size variable in settings file.
		std::cout << "Width: " << windowWidth << " | Height: " << windowHeight << std::endl;
	}
}