#include "KeyboardCallback.h"
#include "GameSettingsHandler.h"
#include "Logger.h"
#include "InputTracker.h"

namespace Bountive
{
	KeyboardCallback* KeyboardCallback::instance = nullptr;
	Logger KeyboardCallback::logger = Logger("KeyboardCallback", Logger::Level::LEVEL_ALL);

	KeyboardCallback* KeyboardCallback::init(GameSettingsHandler& gameSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new KeyboardCallback(gameSettingsHandler);
		}

		return instance;
	}


	KeyboardCallback::KeyboardCallback(GameSettingsHandler& gameSettingsHandler) :
		mGameSettingsHandler(gameSettingsHandler),
		mInputTracker(InputTracker::init(gameSettingsHandler))
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
			instance->mInputTracker->setKeyPressed(asciiValue);
		}
		else if (action == GLFW_RELEASE)
		{
			instance->mInputTracker->setKeyReleased(asciiValue);
		}
	}


	const InputTracker& KeyboardCallback::getInputTracker()
	{
		return *instance->mInputTracker;
	}
}