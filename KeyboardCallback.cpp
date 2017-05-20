#include "KeyboardCallback.h"
#include "GameSettingsHandler.h"
#include "Logger.h"

namespace Bountive
{
	KeyboardCallback* KeyboardCallback::instance = nullptr;
	Logger KeyboardCallback::logger = Logger("KeyboardCallback", Logger::Level::LEVEL_ALL);

	KeyboardCallback* KeyboardCallback::init(const Window& window, GameSettingsHandler& gameSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new KeyboardCallback(window, gameSettingsHandler);
		}

		return instance;
	}


	KeyboardCallback::KeyboardCallback(const Window& window, GameSettingsHandler& gameSettingsHandler) :
		mGameSettingsHandler(gameSettingsHandler),
		mInputTracker(window.getInputTracker())
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