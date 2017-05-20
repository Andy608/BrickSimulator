#pragma once
#ifndef BOUNTIVE_INPUTTRACKER_H_
#define BOUNTIVE_INPUTTRACKER_H_

#include <glew.h>

namespace Bountive
{
	class GameSettingsHandler;
	class Logger;

	class InputTracker
	{
	public:
		static InputTracker* instance;
		
		static InputTracker* init(const GameSettingsHandler& GAME_SETTINGS_HANDLER);

		~InputTracker();

		void setKeyPressed(GLint keyCode);
		void setKeyReleased(GLint keyCode);
		const GLboolean& isKeyEscapePressed() const;

	private:
		static Logger logger;
		static const GLint MAX_KEYS_PRESSED;

		GLint* mPressedKeys;
		const GameSettingsHandler& mGAME_SETTINGS_HANDLER;
		GLboolean mKeyEscapePressed;

		InputTracker(const GameSettingsHandler& GAME_SETTINGS_HANDLER);

		void addKeyPressed(GLint asciiValue);
		void removeKeyPressed(GLint asciiValue);
		void printPressedKeys(GLboolean isPressed) const;
	};
}

#endif