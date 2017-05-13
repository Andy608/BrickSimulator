#pragma once
#ifndef BOUNTIVE_SETTINGSHANDLER_H_
#define BOUNTIVE_SETTINGSHANDLER_H_

#include "FileWriter.h"
#include "FileReader.h"
#include "FileLocation.h"
#include "BoolSettingType.h"

namespace Bountive
{
	class SettingsHandler
	{
	public:
		static SettingsHandler* instance;
		static SettingsHandler* init();

		void updateSettings();
		void loadOptionsFromFile();
		void saveOptionsInFile();

		void setDefaultSettings();

		~SettingsHandler();

	private:
		static const wchar_t DELIMITER;
		static const std::wstring VSYNC;
		static const std::wstring SettingsHandler::FULLSCREEN;
		static const std::wstring SETTINGS_FOLDER_NAME;
		static const std::wstring SETTINGS_FILE_NAME;

		const FileDirectory* mSETTINGS_DIRECTORY;

		FileWriter* mFileWriter;
		FileReader* mFileReader;

		FileLocation* mSettingsFile;
		BooleanSettingType mVsyncEnabled;
		BooleanSettingType mFullScreenEnabled;

		SettingsHandler();
	};
}

#endif