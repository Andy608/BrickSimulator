#include "KeyboardCallback.h"
#include "FileSettingsHandler.h"
#include "Logger.h"

namespace Bountive
{
	KeyboardCallback* KeyboardCallback::instance = nullptr;
	Logger KeyboardCallback::logger = Logger("KeyboardCallback", Logger::Level::LEVEL_ALL);

	KeyboardCallback* KeyboardCallback::init(InputTracker& inputTracker, FileSettingsHandler& fileSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new KeyboardCallback(inputTracker, fileSettingsHandler);
		}

		return instance;
	}


	KeyboardCallback::KeyboardCallback(InputTracker& inputTracker, FileSettingsHandler& fileSettingsHandler) :
		mFileSettingsHandler(fileSettingsHandler),
		mInputTracker(inputTracker)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating KeyboardCallback...");
	}


	KeyboardCallback::~KeyboardCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting KeyboardCallback...");
	}


	void KeyboardCallback::keyCallback(GLFWwindow* windowHandle, GLint asciiValue, GLint scanCode, GLint action, GLint mode)
	{
		if (action == GLFW_PRESS)
		{
			instance->mInputTracker.setKeyPressed(asciiValue);
		}
		else if (action == GLFW_RELEASE)
		{
			instance->mInputTracker.setKeyReleased(asciiValue);
		}
	}
}