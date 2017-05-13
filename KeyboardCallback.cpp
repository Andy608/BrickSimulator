#include "KeyboardCallback.h"
#include <iostream>

namespace Bountive
{
	const GLint KeyboardCallback::MAX_KEYS_PRESSED = 6;
	KeyboardCallback* KeyboardCallback::instance = nullptr;

	KeyboardCallback* KeyboardCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new KeyboardCallback();
		}

		return instance;
	}


	KeyboardCallback::KeyboardCallback() : mPressedKeys(new int[MAX_KEYS_PRESSED]) 
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
				//std::cout << "Key is already pressed." << std::endl;
				break;
			}
			else if (mPressedKeys[i] == NULL)
			{
				//std::cout << "Adding key to the list." << std::endl;
				mPressedKeys[i] = asciiValue;
				break;
			}
		}

		printPressedKeysDebug(true);
	}


	void KeyboardCallback::removeKeyPressed(GLint asciiValue)
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (mPressedKeys[i] == asciiValue)
			{
				//std::cout << "Removing key from the list." << std::endl;
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

		printPressedKeysDebug(false);
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
		}
		else if (action == GLFW_RELEASE)
		{
			instance->removeKeyPressed(asciiValue);

			if (asciiValue == GLFW_KEY_ESCAPE)
			{
				//TODO: Make a boolean in the settings file and set this to true and then handle this somewhere else.
				//TODO: Send keys to input handler
				glfwSetWindowShouldClose(windowHandle, GL_TRUE);
			}
		}
	}
}