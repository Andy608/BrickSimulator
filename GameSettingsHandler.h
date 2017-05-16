#pragma once
#ifndef BOUNTIVE_GAMESETTINGSHANDLER_H_
#define BOUNTIVE_GAMESETTINGSHANDLER_H_

#include "BooleanSetting.h"
#include "ClampedIntegerSetting.h"
#include <glm\vec2.hpp>

namespace Bountive
{
	class FileWriter;
	class FileReader;
	class FileLocation;
	class FileDirectory;

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

		const GLboolean& isSaveWindowState() const;
		const GLint& getWindowWidth() const;
		const GLint& getWindowHeight() const;
		const GLint& getWindowPositionX() const;
		const GLint& getWindowPositionY() const;

		const GLboolean& isVsyncEnabled() const;
		const GLboolean& isFullscreenEnabled() const;
		const GLint& getFieldOfView() const;

		const GLint& getKeyEscape() const;


		void setSaveWindowState(GLboolean saveWindowState);
		void setWindowSizeX(GLint windowSizeX);
		void setWindowSizeY(GLint windowSizeY);
		void setWindowPositionX(GLint windowPositionX);
		void setWindowPositionY(GLint windowPositionY);

		void setVsyncEnabled(GLboolean vsyncEnabled);
		void setFullscreenEnabled(GLboolean fullscreenEnabled);
		void setFieldOfView(GLint fieldOfView);

	private:
		static const std::wstring SETTINGS_FOLDER_NAME;
		static const std::wstring SETTINGS_FILE_NAME;

		const FileDirectory* mSETTINGS_DIRECTORY;

		FileWriter* mFileWriter;
		FileReader* mFileReader;

		FileLocation* mSettingsFile;

		BooleanSetting mSaveWindowState;

		const glm::vec2 mDEFAULT_WINDOW_SIZE;
		const glm::vec2 mDEFAULT_WINDOW_POSITION;

		ClampedIntegerSetting mWindowPositionX;
		ClampedIntegerSetting mWindowPositionY;
		ClampedIntegerSetting mWindowSizeX;
		ClampedIntegerSetting mWindowSizeY;

		BooleanSetting mVsyncEnabled;
		BooleanSetting mFullscreenEnabled;

		ClampedIntegerSetting mFieldOfView;

		IntegerSetting mKeyEscape;

		void setWindowInBounds();
	};
}

#endif