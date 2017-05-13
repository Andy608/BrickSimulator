#include "SettingsHandler.h"
#include "FileUtil.h"
#include <iostream>

namespace Bountive
{
	SettingsHandler* SettingsHandler::instance = nullptr;
	const std::wstring SettingsHandler::SETTINGS_FOLDER_NAME = L"settings";
	const std::wstring SettingsHandler::SETTINGS_FILE_NAME = L"options";

	const wchar_t SettingsHandler::DELIMITER = '=';
	const std::wstring SettingsHandler::VSYNC = L"vsync";
	const std::wstring SettingsHandler::FULLSCREEN = L"fullscreen";

	SettingsHandler* SettingsHandler::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new SettingsHandler();
			}
			catch (std::wstring e)
			{
				std::wcout << e << std::endl;
			}
		}

		return instance;
	}


	SettingsHandler::SettingsHandler()
	try : mSETTINGS_DIRECTORY(FileUtil::createDirectory(FileUtil::instance->getmAppdataDir()->getDirectory(), SETTINGS_FOLDER_NAME)),
		mSettingsFile(new FileLocation(mSETTINGS_DIRECTORY, SETTINGS_FILE_NAME, FileLocation::TXT_EXT)),
		mFileWriter(new FileWriter()),
		mFileReader(new FileReader()),
		mVsyncEnabled(BooleanSettingType(VSYNC, true)),
		mFullScreenEnabled(BooleanSettingType(FULLSCREEN, false))
	{
		mSettingsFile->createFile(mFileWriter->getWriteStream());

		if (mSettingsFile->isCreated())
		{
			std::wcout << "Successfully created settings file! : " << mSettingsFile->getFullPath() << std::endl;
		}
		else
		{
			std::wcout << "There was an error creating the settings file: " << mSettingsFile->getFullPath() << std::endl;
		}

		updateSettings();
	}
	catch (std::wstring e)
	{
		delete mSETTINGS_DIRECTORY;
		delete mSettingsFile;
		delete mFileWriter;
		delete mFileReader;

		mSETTINGS_DIRECTORY = nullptr;
		mSettingsFile = nullptr;

		throw (e);
	}


	SettingsHandler::~SettingsHandler()
	{
		saveOptionsInFile();
		std::wcout << "Deleting SettingsHandler." << std::endl;
		delete mSETTINGS_DIRECTORY;
		delete mSettingsFile;
		delete mFileWriter;
		delete mFileReader;
	}


	void SettingsHandler::updateSettings()
	{
		setDefaultSettings();
		if (mSettingsFile->isCreated())
		{
			loadOptionsFromFile();
		}
	}


	void SettingsHandler::loadOptionsFromFile()
	{
		std::vector<std::wstring> lines = mFileReader->getLinesInFile(*mSettingsFile);

		std::wcout << "LINES LENGTH: " << lines.size() << std::endl;

		for (GLuint i = 0; i < lines.size(); ++i)
		{
			std::wstring line = lines.at(i);
			for (GLuint j = 0; j < line.length(); ++j)
			{
				if (line.c_str()[j] == DELIMITER)
				{
					std::wstring settingName = line.substr(0, j);
					std::wstring settingVar = line.substr(j + 1);
					std::wcout << settingName << "=" << settingVar << std::endl;

					if (settingName.compare(VSYNC) == 0)
					{
						mVsyncEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(FULLSCREEN) == 0)
					{
						mFullScreenEnabled.setCustomBoolean(settingVar);
					}
					else
					{
						std::wcout << "Unknown setting \'" << settingName << "\'. Skipping." << std::endl;
					}
				}
			}
		}
	}


	void SettingsHandler::saveOptionsInFile()
	{
		std::vector<std::wstring> settingsFile;

		settingsFile.push_back(VSYNC + DELIMITER + BooleanSettingType::toString(mVsyncEnabled.getCustomBoolean()));
		settingsFile.push_back(FULLSCREEN + DELIMITER + BooleanSettingType::toString(mFullScreenEnabled.getCustomBoolean()));

		mFileWriter->writeLinesInFile(*mSettingsFile, settingsFile);
	}


	void SettingsHandler::setDefaultSettings()
	{
		mVsyncEnabled.resetBoolean();
		mFullScreenEnabled.resetBoolean();
	}
}