#include <iostream>
#include "KeyboardCallback.h"
#include "GameSettingsHandler.h"
#include "Logger.h"

namespace Bountive
{
	KeyboardCallback* KeyboardCallback::instance = nullptr;
	Logger KeyboardCallback::logger = Logger("KeyboardCallback", Logger::Level::LEVEL_ALL);
	const GLint KeyboardCallback::MAX_KEYS_PRESSED = 6;

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
		mPressedKeys(new int[MAX_KEYS_PRESSED])
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating KeyboardCallback...");

		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			mPressedKeys[i] = NULL;
		}
	}


	KeyboardCallback::~KeyboardCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting KeyboardCallback...");
		delete[] mPressedKeys;
	}


	void KeyboardCallback::addKeyPressed(GLint asciiValue)
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (mPressedKeys[i] == asciiValue)
			{
				break;
			}
			else if (mPressedKeys[i] == NULL)
			{
				mPressedKeys[i] = asciiValue;
				break;
			}
		}

		if (logger.getMinimumLevel() <= Logger::Level::LEVEL_DEBUG)
		{
			printPressedKeysDebug(GL_TRUE);
		}
	}


	void KeyboardCallback::removeKeyPressed(GLint asciiValue)
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (mPressedKeys[i] == asciiValue)
			{
				mPressedKeys[i] = NULL;

				for (int j = i; j < MAX_KEYS_PRESSED - 1; ++j)
				{
					if (mPressedKeys[j + 1] == NULL)
					{
						continue;
					}
					else
					{
						mPressedKeys[j] = mPressedKeys[j + 1];
						mPressedKeys[j + 1] = NULL;
					}
				}
			}
		}

		if (logger.getMinimumLevel() <= Logger::Level::LEVEL_DEBUG)
		{
			printPressedKeysDebug(GL_FALSE);
		}
	}


	void KeyboardCallback::printPressedKeysDebug(GLboolean isPressed) const
	{
		std::string keyList;

		if (isPressed)
		{
			keyList.append("Key Added... | ");
		}
		else
		{
			keyList.append("Key Removed... | ");
		}

		keyList.append("(0: " + std::to_string(instance->mPressedKeys[0]));

		for (int i = 1; i < MAX_KEYS_PRESSED; ++i)
		{
			keyList.append(", " + std::to_string(i) + ": " + std::to_string(instance->mPressedKeys[i]));
		}

		keyList.append(")");

		logger.log(Logger::Level::LEVEL_DEBUG, keyList);
	}


	void KeyboardCallback::keyCallback(GLFWwindow* windowHandle, GLint asciiValue, GLint scanCode, GLint action, GLint mode)
	{
		if (action == GLFW_PRESS)
		{
			instance->addKeyPressed(asciiValue);

			if (asciiValue == instance->mGameSettingsHandler.getKeyEscape().getCustomInteger())
			{
				instance->mIsEscapePressed = GL_TRUE;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			instance->removeKeyPressed(asciiValue);

			if (asciiValue == instance->mGameSettingsHandler.getKeyEscape().getCustomInteger())
			{
				instance->mIsEscapePressed = GL_FALSE;
			}
		}
	}


	const GLboolean& KeyboardCallback::isKeyEscapePressed()
	{
		return instance->mIsEscapePressed;
	}
}