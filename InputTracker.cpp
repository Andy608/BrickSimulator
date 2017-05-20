#include "InputTracker.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"
#include "GameSettingsHandler.h"

namespace Bountive
{
	InputTracker* InputTracker::instance = nullptr;
	Logger InputTracker::logger = Logger("InputTracker", Logger::Level::LEVEL_ALL);
	const GLint InputTracker::MAX_KEYS_PRESSED = 6;

	InputTracker* InputTracker::init(const GameSettingsHandler& GAME_SETTINGS_HANDLER)
	{
		if (instance == nullptr)
		{
			instance = new InputTracker(GAME_SETTINGS_HANDLER);
		}

		return instance;
	}


	InputTracker::InputTracker(const GameSettingsHandler& GAME_SETTINGS_HANDLER) :
		mGAME_SETTINGS_HANDLER(GAME_SETTINGS_HANDLER),
		mPressedKeys(new int[MAX_KEYS_PRESSED]),
		mKeyEscapePressed(GL_FALSE)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating InputHandler...");
	
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			mPressedKeys[i] = NULL;
		}
	}


	InputTracker::~InputTracker()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting InputHandler...");
		delete[] mPressedKeys;
	}


	void InputTracker::setKeyPressed(GLint keyCode)
	{
		addKeyPressed(keyCode);
		if (keyCode = mGAME_SETTINGS_HANDLER.getKeyEscape().getCustomInteger()) mKeyEscapePressed = GL_TRUE;
	}


	void InputTracker::setKeyReleased(GLint keyCode)
	{
		removeKeyPressed(keyCode);
		if (keyCode = mGAME_SETTINGS_HANDLER.getKeyEscape().getCustomInteger()) mKeyEscapePressed = GL_FALSE;
	}


	void InputTracker::addKeyPressed(GLint asciiValue)
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
			printPressedKeys(GL_TRUE);
		}
	}


	void InputTracker::removeKeyPressed(GLint asciiValue)
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
			printPressedKeys(GL_FALSE);
		}
	}


	void InputTracker::printPressedKeys(GLboolean isPressed) const
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


	const GLboolean& InputTracker::isKeyEscapePressed() const
	{
		return mKeyEscapePressed;
	}
}