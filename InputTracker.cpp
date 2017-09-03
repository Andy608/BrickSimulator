#include "InputTracker.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"
#include "FileSettingsHandler.h"
#include "Window.h"

namespace Bountive
{
	InputTracker* InputTracker::instance = nullptr;
	Logger InputTracker::logger = Logger("InputTracker", Logger::Level::LEVEL_ALL);
	const GLint InputTracker::MAX_KEYS_PRESSED = 6;

	InputTracker* InputTracker::init(const FileSettingsHandler& FILE_SETTINGS_HANDLER)
	{
		if (instance == nullptr)
		{
			instance = new InputTracker(FILE_SETTINGS_HANDLER);
		}

		return instance;
	}


	InputTracker::InputTracker(const FileSettingsHandler& FILE_SETTINGS_HANDLER) :
		mFILE_SETTINGS_HANDLER(FILE_SETTINGS_HANDLER),
		mPressedKeys(new int[MAX_KEYS_PRESSED]),
		mPauseKey(FILE_SETTINGS_HANDLER.getPauseKeyCode()),
		mCameraForwardKey(FILE_SETTINGS_HANDLER.getCameraForwardKeyCode()),
		mCameraBackwardKey(FILE_SETTINGS_HANDLER.getCameraBackwardKeyCode()),
		mCameraLeftKey(FILE_SETTINGS_HANDLER.getCameraLeftKeyCode()),
		mCameraRightKey(FILE_SETTINGS_HANDLER.getCameraRightKeyCode()),
		mCameraUpKey(FILE_SETTINGS_HANDLER.getCameraUpKeyCode()),
		mCameraDownKey(FILE_SETTINGS_HANDLER.getCameraDownKeyCode()),
		mCursorPosition(),
		mLastCursorPosition()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating InputTracker...");
	
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

		if (keyCode == mPauseKey->getCustomInteger())
		{
			mPauseKey->setNewPress(GL_TRUE);
			mPauseKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraForwardKey->getCustomInteger())
		{
			mCameraForwardKey->setNewPress(GL_TRUE);
			mCameraForwardKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraBackwardKey->getCustomInteger())
		{
			mCameraBackwardKey->setNewPress(GL_TRUE);
			mCameraBackwardKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraLeftKey->getCustomInteger())
		{
			mCameraLeftKey->setNewPress(GL_TRUE);
			mCameraLeftKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraRightKey->getCustomInteger())
		{
			mCameraRightKey->setNewPress(GL_TRUE);
			mCameraRightKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraUpKey->getCustomInteger())
		{
			mCameraUpKey->setNewPress(GL_TRUE);
			mCameraUpKey->setPressed(GL_TRUE);
		}
		else if (keyCode == mCameraDownKey->getCustomInteger())
		{
			mCameraDownKey->setNewPress(GL_TRUE);
			mCameraDownKey->setPressed(GL_TRUE);
		}
	}


	void InputTracker::setKeyReleased(GLint keyCode)
	{
		removeKeyPressed(keyCode);

		if (keyCode == mPauseKey->getCustomInteger())
		{
			mPauseKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraForwardKey->getCustomInteger())
		{
			mCameraForwardKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraBackwardKey->getCustomInteger())
		{
			mCameraBackwardKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraLeftKey->getCustomInteger())
		{
			mCameraLeftKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraRightKey->getCustomInteger())
		{
			mCameraRightKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraUpKey->getCustomInteger())
		{
			mCameraUpKey->setPressed(GL_FALSE);
		}
		else if (keyCode == mCameraDownKey->getCustomInteger())
		{
			mCameraDownKey->setPressed(GL_FALSE);
		}
	}


	void InputTracker::updateCursorPosition(GLdouble x, GLdouble y)
	{
		if (mLastCursorPosition.x == 0 && mLastCursorPosition.y == 0)
		{
			mLastCursorPosition.x = x;
			mLastCursorPosition.y = y;
		}
		else
		{
			mLastCursorPosition.x = mCursorPosition.x;
			mLastCursorPosition.y = mCursorPosition.y;
		}

		mCursorPosition.x = static_cast<GLfloat>(x);
		mCursorPosition.y = static_cast<GLfloat>(y);

		//logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mLastCursorPosition.x) + " " + std::to_string(mCursorPosition.x));
	}


	void InputTracker::setCursorPosition(Window& window, glm::vec2 cursorPosition)
	{
		glfwSetCursorPos(window.getWindowHandle(), cursorPosition.x, cursorPosition.y);
		updateCursorPosition(cursorPosition.x, cursorPosition.y);

		//logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mLastCursorPosition.x) + " " + std::to_string(mCursorPosition.x));
	}


	void InputTracker::update(const GLdouble& DELTA_TIME)
	{
		if (mPauseKey->isNewPress())
		{
			mPauseKey->setNewPress(GL_FALSE);
		}
		else if (mCameraForwardKey->isNewPress())
		{
			mCameraForwardKey->setNewPress(GL_FALSE);
		}
		else if (mCameraBackwardKey->isNewPress())
		{
			mCameraBackwardKey->setNewPress(GL_FALSE);
		}
		else if (mCameraLeftKey->isNewPress())
		{
			mCameraLeftKey->setNewPress(GL_FALSE);
		}
		else if (mCameraRightKey->isNewPress())
		{
			mCameraRightKey->setNewPress(GL_FALSE);
		}
		else if (mCameraUpKey->isNewPress())
		{
			mCameraUpKey->setNewPress(GL_FALSE);
		}
		else if (mCameraDownKey->isNewPress())
		{
			mCameraDownKey->setNewPress(GL_FALSE);
		}

		updateCursorPosition(mCursorPosition.x, mCursorPosition.y);
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
		return *mPauseKey;
	}

	const SingleKeySetting& InputTracker::getCameraForwardKey() const
	{
		return *mCameraForwardKey;
	}


	const SingleKeySetting& InputTracker::getCameraBackwardKey() const
	{
		return *mCameraBackwardKey;
	}


	const SingleKeySetting& InputTracker::getCameraLeftKey() const
	{
		return *mCameraLeftKey;
	}


	const SingleKeySetting& InputTracker::getCameraRightKey() const
	{
		return *mCameraRightKey;
	}


	const SingleKeySetting& InputTracker::getCameraUpKey() const
	{
		return *mCameraUpKey;
	}


	const SingleKeySetting& InputTracker::getCameraDownKey() const
	{
		return *mCameraDownKey;
	}


	const glm::vec2& InputTracker::getCursorPosition() const
	{
		return mCursorPosition;
	}


	const glm::vec2& InputTracker::getLastCursorPosition() const
	{
		return mLastCursorPosition;
	}
}