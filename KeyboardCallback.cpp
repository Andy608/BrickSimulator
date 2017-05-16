#include <iostream>
#include "KeyboardCallback.h"
#include "GameSettingsHandler.h"

namespace Bountive
{
	const GLint KeyboardCallback::MAX_KEYS_PRESSED = 6;
	KeyboardCallback* KeyboardCallback::instance = nullptr;

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
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			mPressedKeys[i] = NULL;
		}
	}


	KeyboardCallback::~KeyboardCallback()
	{
		std::cout << "Deleting KeyboardCallback." << std::endl;
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

		//printPressedKeysDebug(true);
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

		//printPressedKeysDebug(false);
	}


	void KeyboardCallback::printPressedKeysDebug(GLboolean isPressed) const
	{
		if (isPressed)
		{
			std::cout << "Key Added... | ";
		}
		else
		{
			std::cout << "Key Removed... | ";
		}

		std::cout << "(" << 0 << ": " << instance->mPressedKeys[0];

		for (int i = 1; i < MAX_KEYS_PRESSED; ++i)
		{
			std::cout << ", " << i << ": " << instance->mPressedKeys[i];
		}

		std::cout << ")" << std::endl;
	}


	void KeyboardCallback::keyCallback(GLFWwindow* windowHandle, GLint asciiValue, GLint scanCode, GLint action, GLint mode)
	{
		if (action == GLFW_PRESS)
		{
			instance->addKeyPressed(asciiValue);

			std::wcout << asciiValue << std::endl;

			if (asciiValue == instance->mGameSettingsHandler.getKeyEscape())
			{
				instance->mIsEscapePressed = GL_TRUE;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			instance->removeKeyPressed(asciiValue);

			if (asciiValue == instance->mGameSettingsHandler.getKeyEscape())
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