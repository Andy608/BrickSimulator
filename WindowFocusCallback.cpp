#include "WindowFocusCallback.h"
#include "Logger.h"

namespace Bountive
{
	WindowFocusCallback* WindowFocusCallback::instance = nullptr;
	Logger WindowFocusCallback::logger = Logger("WindowFocusCallback", Logger::Level::LEVEL_ALL);

	WindowFocusCallback* WindowFocusCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new WindowFocusCallback();
		}

		return instance;
	}


	WindowFocusCallback::WindowFocusCallback() 
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating WindowFocusCallback...");
	}


	WindowFocusCallback::~WindowFocusCallback() 
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting WindowFocusCallback...");
	}


	void WindowFocusCallback::windowFocusCallback(GLFWwindow* windowHandle, GLint isFocused)
	{
		//TODO: Set focus variable in settings file.
		if (isFocused)
		{
			logger.log(Logger::Level::LEVEL_TRACE, "Window focused.");
		}
		else
		{
			logger.log(Logger::Level::LEVEL_TRACE, "Window unfocused.");
		}
	}
}