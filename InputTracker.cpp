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
		mPause(SingleKeySetting(GAME_SETTINGS_HANDLER.getPauseKeyCode())),
		mCameraForward(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraForwardKeyCode())),
		mCameraBackward(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraBackwardKeyCode())),
		mCameraLeft(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraLeftKeyCode())),
		mCameraRight(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraRightKeyCode())),
		mCameraUp(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraUpKeyCode())),
		mCameraDown(SingleKeySetting(GAME_SETTINGS_HANDLER.getCameraDownKeyCode()))
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

		if (keyCode == mPause.getCustomInteger())
		{
			mPause.setNewPress(GL_TRUE);
			mPause.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraForward.getCustomInteger())
		{
			mCameraForward.setNewPress(GL_TRUE);
			mCameraForward.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraBackward.getCustomInteger())
		{
			mCameraBackward.setNewPress(GL_TRUE);
			mCameraBackward.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraLeft.getCustomInteger())
		{
			mCameraLeft.setNewPress(GL_TRUE);
			mCameraLeft.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraRight.getCustomInteger())
		{
			mCameraRight.setNewPress(GL_TRUE);
			mCameraRight.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraUp.getCustomInteger())
		{
			mCameraUp.setNewPress(GL_TRUE);
			mCameraUp.setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraDown.getCustomInteger())
		{
			mCameraDown.setNewPress(GL_TRUE);
			mCameraDown.setPressed(GL_TRUE);
		}
	}


	void InputTracker::setKeyReleased(GLint keyCode)
	{
		removeKeyPressed(keyCode);

		if (keyCode == mPause.getCustomInteger())
		{
			mPause.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraForward.getCustomInteger())
		{
			mCameraForward.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraBackward.getCustomInteger())
		{
			mCameraBackward.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraLeft.getCustomInteger())
		{
			mCameraLeft.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraRight.getCustomInteger())
		{
			mCameraRight.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraUp.getCustomInteger())
		{
			mCameraUp.setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraDown.getCustomInteger())
		{
			mCameraDown.setPressed(GL_FALSE);
		}
	}


	void InputTracker::update(const GLdouble& DELTA_TIME)
	{
		if (mPause.isNewPress())
		{
			mPause.setNewPress(GL_FALSE);
		}
		else if (mCameraForward.isNewPress())
		{
			mCameraForward.setNewPress(GL_FALSE);
		}
		else if (mCameraBackward.isNewPress())
		{
			mCameraBackward.setNewPress(GL_FALSE);
		}
		else if (mCameraLeft.isNewPress())
		{
			mCameraLeft.setNewPress(GL_FALSE);
		}
		else if (mCameraRight.isNewPress())
		{
			mCameraRight.setNewPress(GL_FALSE);
		}
		else if (mCameraUp.isNewPress())
		{
			mCameraUp.setNewPress(GL_FALSE);
		}
		else if (mCameraDown.isNewPress())
		{
			mCameraDown.setNewPress(GL_FALSE);
		}
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


	const SingleKeySetting& InputTracker::getPauseKey() const
	{
		return mPause;
	}

	const SingleKeySetting& InputTracker::getCameraForwardKey() const
	{
		return mCameraForward;
	}


	const SingleKeySetting& InputTracker::getCameraBackwardKey() const
	{
		return mCameraBackward;
	}


	const SingleKeySetting& InputTracker::getCameraLeftKey() const
	{
		return mCameraLeft;
	}


	const SingleKeySetting& InputTracker::getCameraRightKey() const
	{
		return mCameraRight;
	}


	const SingleKeySetting& InputTracker::getCameraUpKey() const
	{
		return mCameraUp;
	}


	const SingleKeySetting& InputTracker::getCameraDownKey() const
	{
		return mCameraDown;
	}
}