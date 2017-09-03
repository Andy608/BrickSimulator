#pragma once
#ifndef BOUNTIVE_INPUTTRACKER_H_
#define BOUNTIVE_INPUTTRACKER_H_

#include <glew.h>
#include <glm\vec2.hpp>
#include "SingleKeySetting.h"

namespace Bountive
{
	class FileSettingsHandler;
	class Window;
	class Logger;

	class InputTracker
	{
	public:
		static InputTracker* instance;

		static InputTracker* init(const FileSettingsHandler& FILE_SETTINGS_HANDLER);

		~InputTracker();

		void setKeyPressed(GLint keyCode);
		void setKeyReleased(GLint keyCode);

		void updateCursorPosition(GLdouble x, GLdouble y);
		void setCursorPosition(Window& window, glm::vec2 cursorPosition);

		void update(const GLdouble& DELTA_TIME);

		const SingleKeySetting& getPauseKey() const;

		const SingleKeySetting& getCameraForwardKey() const;
		const SingleKeySetting& getCameraBackwardKey() const;
		const SingleKeySetting& getCameraLeftKey() const;
		const SingleKeySetting& getCameraRightKey() const;
		const SingleKeySetting& getCameraUpKey() const;
		const SingleKeySetting& getCameraDownKey() const;

		const glm::vec2& getCursorPosition() const;
		const glm::vec2& getLastCursorPosition() const;

	private:
		static Logger logger;
		static const GLint MAX_KEYS_PRESSED;

		GLint* mPressedKeys;
		const FileSettingsHandler& mFILE_SETTINGS_HANDLER;

		SingleKeySetting* mPauseKey;

		SingleKeySetting* mCameraForwardKey;
		SingleKeySetting* mCameraBackwardKey;
		SingleKeySetting* mCameraLeftKey;
		SingleKeySetting* mCameraRightKey;
		SingleKeySetting* mCameraUpKey;
		SingleKeySetting* mCameraDownKey;

		glm::vec2 mCursorPosition;
		glm::vec2 mLastCursorPosition;

		InputTracker(const FileSettingsHandler& FILE_SETTINGS_HANDLER);

		void addKeyPressed(GLint asciiValue);
		void removeKeyPressed(GLint asciiValue);
		void printPressedKeys(GLboolean isPressed) const;
	};
}

#endif