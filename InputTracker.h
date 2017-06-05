#pragma once
#ifndef BOUNTIVE_INPUTTRACKER_H_
#define BOUNTIVE_INPUTTRACKER_H_

#include <glew.h>
#include "SingleKeySetting.h"

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

		void update(const GLdouble& DELTA_TIME);

		const SingleKeySetting& getPauseKey() const;

		const SingleKeySetting& getCameraForwardKey() const;
		const SingleKeySetting& getCameraBackwardKey() const;
		const SingleKeySetting& getCameraLeftKey() const;
		const SingleKeySetting& getCameraRightKey() const;
		const SingleKeySetting& getCameraUpKey() const;
		const SingleKeySetting& getCameraDownKey() const;

	private:
		static Logger logger;
		static const GLint MAX_KEYS_PRESSED;

		GLint* mPressedKeys;
		const GameSettingsHandler& mGAME_SETTINGS_HANDLER;

		SingleKeySetting mPause;

		SingleKeySetting mCameraForward;
		SingleKeySetting mCameraBackward;
		SingleKeySetting mCameraLeft;
		SingleKeySetting mCameraRight;
		SingleKeySetting mCameraUp;
		SingleKeySetting mCameraDown;

		InputTracker(const GameSettingsHandler& GAME_SETTINGS_HANDLER);

		void addKeyPressed(GLint asciiValue);
		void removeKeyPressed(GLint asciiValue);
		void printPressedKeys(GLboolean isPressed) const;
	};
}

#endif