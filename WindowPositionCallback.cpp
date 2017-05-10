#include "WindowPositionCallback.h"
#include <iostream>

namespace Bountive
{
	WindowPositionCallback* WindowPositionCallback::instance = nullptr;

	WindowPositionCallback* WindowPositionCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new WindowPositionCallback();
		}

		return instance;
	}


	WindowPositionCallback::WindowPositionCallback() {}


	WindowPositionCallback::~WindowPositionCallback()
	{
		std::cout << "Deleting WindowPositionCallback." << std::endl;
	}


	void WindowPositionCallback::windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition)
	{
		//TODO: Save position in options
		std::cout << "Window Position: (" << xPosition << ", " << yPosition << ")" << std::endl;
	}
}