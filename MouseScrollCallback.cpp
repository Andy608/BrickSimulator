#include <iostream>
#include "MouseScrollCallback.h"
#include "Logger.h"

namespace Bountive
{
	MouseScrollCallback* MouseScrollCallback::instance = nullptr;
	Logger MouseScrollCallback::logger = Logger("MouseScrollCallback", Logger::Level::LEVEL_ALL);

	MouseScrollCallback* MouseScrollCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new MouseScrollCallback();
		}

		return instance;
	}


	MouseScrollCallback::MouseScrollCallback() 
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating MouseScrollCallback...");
	}


	MouseScrollCallback::~MouseScrollCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting MouseScrollCallback...");
	}


	void MouseScrollCallback::mouseScrollCallback(GLFWwindow* windowHandle, GLdouble xOffset, GLdouble yOffset)
	{
		//TODO: Save scroll in input handler
		logger.log(Logger::Level::LEVEL_TRACE, "Mouse Scroll Offset: (" + std::to_string(xOffset) + ", " + std::to_string(yOffset) + ")");
	}
}