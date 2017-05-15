#pragma once
#ifndef BOUNTIVE_GAMESETTINGSHANDLER_H_
#define BOUNTIVE_GAMESETTINGSHANDLER_H_

#include "FileWriter.h"
#include "FileReader.h"
#include "FileLocation.h"
#include "BooleanSetting.h"
#include "ClampedIntegerSetting.h"
#include <glm\vec2.hpp>

namespace Bountive
{
	class GameSettingsHandler
	{
	public:
		static GameSettingsHandler* instance;
		static GameSettingsHandler* init();

		~GameSettingsHandler();

		void updateSettings();
		void loadOptionsFromFile();
		void saveOptionsInFile();

		void setDefaultSettings();
		void setDefaultWindowState();

		const GLint& getWindowWidth() const;
		const GLint& getWindowHeight() const;

		const GLint& getWindowPositionX() const;
		const GLint& getWindowPositionY() const;

		void setWindowSizeX(GLint windowSizeX);
		void setWindowSizeY(GLint windowSizeY);

		void setWindowPositionX(GLint windowPositionX);
		void setWindowPositionY(GLint windowPositionY);

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
		BooleanSetting mFullScreenEnabled;

		ClampedIntegerSetting mFieldOfView;
		
		GameSettingsHandler();

		void setWindowInBounds();
	};
}

#endif