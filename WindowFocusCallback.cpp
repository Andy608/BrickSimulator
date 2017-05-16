#include <iostream>
#include "WindowFocusCallback.h"

namespace Bountive
{
	WindowFocusCallback* WindowFocusCallback::instance = nullptr;

	WindowFocusCallback* WindowFocusCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new WindowFocusCallback();
		}

		return instance;
	}


	WindowFocusCallback::WindowFocusCallback() {}


	WindowFocusCallback::~WindowFocusCallback() 
	{
		std::cout << "Deleting WindowFocusCallback." << std::endl;
	}


	void WindowFocusCallback::windowFocusCallback(GLFWwindow* windowHandle, GLint isFocused)
	{
		//TODO: Set focus variable in settings file.
		if (isFocused)
		{
			std::cout << "Window focused." << std::endl;
		}
		else
		{
			std::cout << "Window unfocused." << std::endl;
		}
	}
}