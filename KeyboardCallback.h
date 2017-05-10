#pragma once
#ifndef BOUNTIVE_KEYBOARDCALLBACK_H_
#define BOUNTIVE_KEYBOARDCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class KeyboardCallback
	{
	public:
		static KeyboardCallback* instance;

		static KeyboardCallback* init();
		static void keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode);

		void addKeyPressed(const GLint& asciiValue);
		void removeKeyPressed(const GLint& asciiValue);

		void printPressedKeysDebug(GLboolean isPressed) const;

		~KeyboardCallback();

	private:
		const static GLint MAX_KEYS_PRESSED;
		GLint* mPressedKeys;

		KeyboardCallback();
	};
}

#endif