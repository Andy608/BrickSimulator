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


	KeyboardCallback::KeyboardCallback() : pressedKeys(new int[MAX_KEYS_PRESSED]) 
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			pressedKeys[i] = NULL;
		}
	}


	KeyboardCallback::~KeyboardCallback()
	{
		std::cout << "Deleting pressedKeys." << std::endl;
		delete[] pressedKeys;
	}


	void KeyboardCallback::addKeyPressed(const GLint& asciiValue)
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (pressedKeys[i] == asciiValue)
			{
				//std::cout << "Key is already pressed." << std::endl;
				break;
			}
			else if (pressedKeys[i] == NULL)
			{
				//std::cout << "Adding key to the list." << std::endl;
				pressedKeys[i] = asciiValue;
				break;
			}
		}

		printPressedKeys(true);
	}


	void KeyboardCallback::removeKeyPressed(const GLint& asciiValue)
	{
		for (int i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (pressedKeys[i] == asciiValue)
			{
				//std::cout << "Removing key from the list." << std::endl;
				pressedKeys[i] = NULL;
				
				for (int j = i; j < MAX_KEYS_PRESSED - 1; ++j)
				{
					if (pressedKeys[j + 1] == NULL)
					{
						continue;
					}
					else
					{
						pressedKeys[j] = pressedKeys[j + 1];
						pressedKeys[j + 1] = NULL;
					}
				}
			}
		}

		printPressedKeys(false);
	}


	void KeyboardCallback::printPressedKeys(GLboolean isPressed) const
	{
		if (isPressed)
		{
			std::cout << "Key Added... | ";
		}
		else
		{
			std::cout << "Key Removed... | ";
		}

		std::cout << "(" << 0 << ": " << instance->pressedKeys[0];

		for (int i = 1; i < MAX_KEYS_PRESSED; ++i)
		{
			std::cout << ", " << i << ": " << instance->pressedKeys[i];
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
				glfwSetWindowShouldClose(windowHandle, GL_TRUE);
			}
		}
	}
}