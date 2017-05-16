#include <iostream>
#include "MouseScrollCallback.h"

namespace Bountive
{
	MouseScrollCallback* MouseScrollCallback::instance = nullptr;

	MouseScrollCallback* MouseScrollCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new MouseScrollCallback();
		}

		return instance;
	}


	MouseScrollCallback::MouseScrollCallback() {}


	MouseScrollCallback::~MouseScrollCallback()
	{
		std::cout << "Deleting MouseScrollCallback." << std::endl;
	}


	void MouseScrollCallback::mouseScrollCallback(GLFWwindow* windowHandle, GLdouble xOffset, GLdouble yOffset)
	{
		//TODO: Save scroll in input handler
		//std::cout << "Mouse Scroll Offset: (" << xOffset << ", " << yOffset << ")" << std::endl;
	}
}