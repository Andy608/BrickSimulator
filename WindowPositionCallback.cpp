#include "WindowPositionCallback.h"
#include "Logger.h"

namespace Bountive
{
	WindowPositionCallback* WindowPositionCallback::instance = nullptr;
	Logger WindowPositionCallback::logger = Logger("WindowPositionCallback", Logger::Level::LEVEL_ALL);

	WindowPositionCallback* WindowPositionCallback::init(FileSettingsHandler& fileSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new WindowPositionCallback(fileSettingsHandler);
		}

		return instance;
	}


	WindowPositionCallback::WindowPositionCallback(FileSettingsHandler& fileSettingsHandler) :
		mFileSettingsHandler(fileSettingsHandler)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating WindowPositionCallback...");
	}


	WindowPositionCallback::~WindowPositionCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting WindowPositionCallback...");
	}


	void WindowPositionCallback::windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition)
	{
		if (!instance->mFileSettingsHandler.isWindowMaximized().getCustomBoolean())
		{
			instance->mFileSettingsHandler.setWindowPositionX(xPosition);
			instance->mFileSettingsHandler.setWindowPositionY(yPosition);
		}
	}
}