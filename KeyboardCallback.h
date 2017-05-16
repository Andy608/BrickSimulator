#pragma once
#ifndef BOUNTIVE_KEYBOARDCALLBACK_H_
#define BOUNTIVE_KEYBOARDCALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class GameSettingsHandler;

	class KeyboardCallback
	{
	public:
		static KeyboardCallback* instance;

		static KeyboardCallback* init(GameSettingsHandler& gameSettingsHandler);
		static void keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode);

		void addKeyPressed(GLint asciiValue);
		void removeKeyPressed(GLint asciiValue);

		void printPressedKeysDebug(GLboolean isPressed) const;

		const static GLboolean& isKeyEscapePressed();

		~KeyboardCallback();

	private:
		const static GLint MAX_KEYS_PRESSED;

		GameSettingsHandler& mGameSettingsHandler;
		GLint* mPressedKeys;

		GLboolean mIsEscapePressed;

		KeyboardCallback(GameSettingsHandler& gameSettingsHandler);
	};
}

#endif