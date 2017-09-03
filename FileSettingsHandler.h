#pragma once
#ifndef BOUNTIVE_FILESETTINGSHANDLER_H_
#define BOUNTIVE_FILESETTINGSHANDLER_H_

#include <glm\vec2.hpp>
#include "BooleanSetting.h"
#include "ClampedIntegerSetting.h"
#include "SingleKeySetting.h"

namespace Bountive
{
	class FileWriter;
	class FileReader;
	class FileLocation;
	class FileDirectory;
	class Window;
	class Logger;
	enum class EnumProjection : GLuint;

	class FileSettingsHandler
	{
	public:
		FileSettingsHandler(const Window& window);
		~FileSettingsHandler();

		void updateSettings();
		void loadOptionsFromFile();
		void saveOptionsToFile();

		void setDefaultSettings();
		void setDefaultWindowState();

		const BooleanSetting& isSaveWindowState() const;
		const BooleanSetting& isWindowMaximized() const;
		const ClampedIntegerSetting& getWindowWidth() const;
		const ClampedIntegerSetting& getWindowHeight() const;
		const ClampedIntegerSetting& getWindowPositionX() const;
		const ClampedIntegerSetting& getWindowPositionY() const;

		BooleanSetting* isVsyncEnabled() const;
		BooleanSetting* isFullscreenEnabled() const;
		ClampedIntegerSetting* getProjectionID() const;
		ClampedIntegerSetting* getFieldOfView() const;

		void setSaveWindowState(GLboolean saveWindowState);
		void setWindowMaximized(GLboolean windowMaximized);
		void setWindowSizeX(GLint windowSizeX);
		void setWindowSizeY(GLint windowSizeY);
		void setWindowPositionX(GLint windowPositionX);
		void setWindowPositionY(GLint windowPositionY);

		void setVsyncEnabled(GLboolean vsyncEnabled);
		void setFullscreenEnabled(GLboolean fullscreenEnabled);
		void setProjectionID(const EnumProjection& projectionType);
		void setFieldOfView(GLint fieldOfView);


		SingleKeySetting* getPauseKeyCode() const;

		SingleKeySetting* getCameraForwardKeyCode() const;
		SingleKeySetting* getCameraBackwardKeyCode() const;
		SingleKeySetting* getCameraLeftKeyCode() const;
		SingleKeySetting* getCameraRightKeyCode() const;
		SingleKeySetting* getCameraUpKeyCode() const;
		SingleKeySetting* getCameraDownKeyCode() const;

	private:
		static Logger logger;
		static const std::wstring SETTINGS_FOLDER_NAME;
		static const std::wstring SETTINGS_FILE_NAME;

		const FileDirectory* mSETTINGS_DIRECTORY;

		FileWriter* mFileWriter;
		FileReader* mFileReader;

		FileLocation* mSettingsFile;

		BooleanSetting mSaveWindowState;

		const glm::vec2 mDEFAULT_WINDOW_SIZE;
		const glm::vec2 mDEFAULT_WINDOW_POSITION;

		BooleanSetting mWindowMaximized;
		ClampedIntegerSetting mWindowPositionX;
		ClampedIntegerSetting mWindowPositionY;
		ClampedIntegerSetting mWindowSizeX;
		ClampedIntegerSetting mWindowSizeY;

		BooleanSetting* mVsyncEnabled;
		BooleanSetting* mFullscreenEnabled;

		ClampedIntegerSetting* mProjectionID;
		ClampedIntegerSetting* mFieldOfView;

		SingleKeySetting* mPauseKeyCode;

		SingleKeySetting* mCameraForwardKeyCode;
		SingleKeySetting* mCameraBackwardKeyCode;
		SingleKeySetting* mCameraLeftKeyCode;
		SingleKeySetting* mCameraRightKeyCode;
		SingleKeySetting* mCameraUpKeyCode;
		SingleKeySetting* mCameraDownKeyCode;

		void setWindowInBounds();
		void checkToResetInvalidWindow();
	};
}

#endif