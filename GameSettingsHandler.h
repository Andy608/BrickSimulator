#pragma once
#ifndef BOUNTIVE_GAMESETTINGSHANDLER_H_
#define BOUNTIVE_GAMESETTINGSHANDLER_H_

#include <glm\vec2.hpp>
#include "BooleanSetting.h"
#include "ClampedIntegerSetting.h"

namespace Bountive
{
	class FileWriter;
	class FileReader;
	class FileLocation;
	class FileDirectory;
	class Logger;

	class GameSettingsHandler
	{
	public:
		GameSettingsHandler();
		~GameSettingsHandler();

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

		const BooleanSetting& isVsyncEnabled() const;
		const BooleanSetting& isFullscreenEnabled() const;
		const ClampedIntegerSetting& getFieldOfView() const;

		const IntegerSetting& getKeyEscape() const;


		void setSaveWindowState(GLboolean saveWindowState);
		void setWindowMaximized(GLboolean windowMaximized);
		void setWindowSizeX(GLint windowSizeX);
		void setWindowSizeY(GLint windowSizeY);
		void setWindowPositionX(GLint windowPositionX);
		void setWindowPositionY(GLint windowPositionY);

		void setVsyncEnabled(GLboolean vsyncEnabled);
		void setFullscreenEnabled(GLboolean fullscreenEnabled);
		void setFieldOfView(GLint fieldOfView);

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

		BooleanSetting mVsyncEnabled;
		BooleanSetting mFullscreenEnabled;

		ClampedIntegerSetting mFieldOfView;

		IntegerSetting mKeyEscape;

		void setWindowInBounds();
		void checkToResetInvalidWindow();
	};
}

#endif