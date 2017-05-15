#include "GameSettingsHandler.h"
#include "DirectoryUtil.h"
#include "Window.h"
#include <iostream>

namespace Bountive
{
	GameSettingsHandler* GameSettingsHandler::instance = nullptr;
	const std::wstring GameSettingsHandler::SETTINGS_FOLDER_NAME = L"settings";
	const std::wstring GameSettingsHandler::SETTINGS_FILE_NAME = L"options";

	GameSettingsHandler* GameSettingsHandler::init()
	{
		if (instance == nullptr)
		{
			try
			{
				instance = new GameSettingsHandler();
				instance->updateSettings();
			}
			catch (std::wstring e)
			{
				std::wcout << e << std::endl;
			}
		}

		return instance;
	}


	GameSettingsHandler::GameSettingsHandler()
		try : mSETTINGS_DIRECTORY(DirectoryUtil::createDirectory(DirectoryUtil::instance->getmAppdataDir()->getDirectory(), SETTINGS_FOLDER_NAME)),
		mSettingsFile(new FileLocation(mSETTINGS_DIRECTORY, SETTINGS_FILE_NAME, FileLocation::TXT_EXT)),
		mFileWriter(new FileWriter()),
		mFileReader(new FileReader()),
		mSaveWindowState(BooleanSetting(L"save_window_state", false)),
		mDEFAULT_WINDOW_SIZE(glm::vec2(Window::instance->mVIDEO_MODE->width / 2.0f, Window::instance->mVIDEO_MODE->height / 2.0f)),
		mDEFAULT_WINDOW_POSITION(glm::vec2((Window::instance->mVIDEO_MODE->width - mDEFAULT_WINDOW_SIZE.x) / 2.0f, (Window::instance->mVIDEO_MODE->height - mDEFAULT_WINDOW_SIZE.y) / 2.0f)),
		mWindowPositionX(ClampedIntegerSetting(L"window_position_x", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.x), 0, static_cast<GLint>(Window::instance->getMaximumWindowPosition().x))),
		mWindowPositionY(ClampedIntegerSetting(L"window_position_y", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.y), 0, static_cast<GLint>(Window::instance->getMaximumWindowPosition().y))),
		mWindowSizeX(ClampedIntegerSetting(L"window_size_x", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.x), static_cast<GLint>(Window::instance->mMINIMUM_SIZE_X), static_cast<GLint>(Window::instance->mMAXIMUM_SIZE_X))),
		mWindowSizeY(ClampedIntegerSetting(L"window_size_y", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.y), static_cast<GLint>(Window::instance->mMINIMUM_SIZE_Y), static_cast<GLint>(Window::instance->mMAXIMUM_SIZE_Y))),
		mVsyncEnabled(BooleanSetting(L"vsync", true)),
		mFullScreenEnabled(BooleanSetting(L"fullscreen", false)),
		mFieldOfView(ClampedIntegerSetting(L"fov", 67, 30, 120))
	{
		std::wcout << "SIZE: " << mDEFAULT_WINDOW_SIZE.x << ", " << mDEFAULT_WINDOW_SIZE.y << std::endl;
		std::wcout << "POS: " << mDEFAULT_WINDOW_POSITION.x << ", " << mDEFAULT_WINDOW_POSITION.y << std::endl;
		std::wcout << "RIP: " << mWindowPositionX.getCustomInteger() << std::endl;

		mSettingsFile->createFile(mFileWriter->getWriteStream());

		if (mSettingsFile->isCreated())
		{
			std::wcout << "Successfully created settings file! : " << mSettingsFile->getFullPath() << std::endl;
		}
		else
		{
			std::wcout << "There was an error creating the settings file: " << mSettingsFile->getFullPath() << std::endl;
		}
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


	GameSettingsHandler::~GameSettingsHandler()
	{
		saveOptionsInFile();
		std::wcout << "Deleting SettingsHandler." << std::endl;
		delete mSETTINGS_DIRECTORY;
		delete mSettingsFile;
		delete mFileWriter;
		delete mFileReader;
	}


	void GameSettingsHandler::updateSettings()
	{
		if (mSettingsFile->isCreated())
		{
			loadOptionsFromFile();

			if (mSaveWindowState.getCustomBoolean())
			{
				setWindowInBounds();
			}
		}
	}


	void GameSettingsHandler::loadOptionsFromFile()
	{
		std::vector<std::wstring> lines = mFileReader->getLinesInFile(*mSettingsFile);

		std::wcout << "LINES LENGTH: " << lines.size() << std::endl;

		for (GLuint i = 0; i < lines.size(); ++i)
		{
			std::wstring line = lines.at(i);
			for (GLuint j = 0; j < line.length(); ++j)
			{
				if (line.c_str()[j] == SettingType::DELIMITER)
				{
					std::wstring settingName = line.substr(0, j);
					std::wstring settingVar = line.substr(j + 1);
					std::wcout << settingName << "=" << settingVar << std::endl;

					if (settingName.compare(mSaveWindowState.getSettingName()) == 0)
					{
						mSaveWindowState.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mWindowPositionX.getSettingName()) == 0)
					{
						mWindowPositionX.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mWindowPositionY.getSettingName()) == 0)
					{
						mWindowPositionY.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mWindowSizeX.getSettingName()) == 0)
					{
						mWindowSizeX.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mWindowSizeY.getSettingName()) == 0)
					{
						mWindowSizeY.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mFullScreenEnabled.getSettingName()) == 0)
					{
						mFullScreenEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mVsyncEnabled.getSettingName()) == 0)
					{
						mVsyncEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mFieldOfView.getSettingName()) == 0)
					{
						mFieldOfView.IntegerSetting::setCustomInteger(settingVar);
					}
					else
					{
						std::wcout << "Unknown setting \'" << settingName << "\'. Skipping." << std::endl;
					}
				}
			}
		}
	}


	void GameSettingsHandler::saveOptionsInFile()
	{
		std::vector<std::wstring> settingsFile;

		settingsFile.push_back(mSaveWindowState);

		if (!mSaveWindowState.getCustomBoolean())
		{
			setDefaultWindowState();
		}

		settingsFile.push_back(mWindowPositionX);
		settingsFile.push_back(mWindowPositionY);
		settingsFile.push_back(mWindowSizeX);
		settingsFile.push_back(mWindowSizeY);

		settingsFile.push_back(mFullScreenEnabled);
		settingsFile.push_back(mVsyncEnabled);
		
		settingsFile.push_back(mFieldOfView);

		mFileWriter->writeLinesInFile(*mSettingsFile, settingsFile);
	}


	void GameSettingsHandler::setDefaultSettings()
	{
		mSaveWindowState.resetCustomValue();
		setDefaultWindowState();

		mFullScreenEnabled.resetCustomValue();
		mVsyncEnabled.resetCustomValue();

		mFieldOfView.resetCustomValue();
	}


	void GameSettingsHandler::setDefaultWindowState()
	{
		mWindowPositionX.resetCustomValue();
		mWindowPositionY.resetCustomValue();
		mWindowSizeX.resetCustomValue();
		mWindowSizeY.resetCustomValue();
	}


	void GameSettingsHandler::setWindowInBounds()
	{
		if (mWindowPositionX.getCustomInteger() < 0)
		{
			mWindowPositionX.setCustomInteger(0);
		}
		else if (mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() > Window::instance->mVIDEO_MODE->width)
		{
			mWindowPositionX.setCustomInteger(mWindowPositionX.getCustomInteger() - 
				(mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() - Window::instance->mVIDEO_MODE->width));
		}

		if (mWindowPositionY.getCustomInteger() < 0)
		{
			mWindowPositionY.setCustomInteger(0);
		}
		else if (mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() > Window::instance->mVIDEO_MODE->height)
		{
			mWindowPositionY.setCustomInteger(mWindowPositionY.getCustomInteger() -
				(mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() - Window::instance->mVIDEO_MODE->height));
		}
	}


	const GLint& GameSettingsHandler::getWindowWidth() const
	{
		return mWindowSizeX.getCustomInteger();
	}


	const GLint& GameSettingsHandler::getWindowHeight() const
	{
		return mWindowSizeY.getCustomInteger();
	}

	const GLint& GameSettingsHandler::getWindowPositionX() const
	{
		return mWindowPositionX.getCustomInteger();
	}


	const GLint& GameSettingsHandler::getWindowPositionY() const
	{
		return mWindowPositionY.getCustomInteger();
	}


	void GameSettingsHandler::setWindowSizeX(GLint windowSizeX)
	{
		mWindowSizeX.setCustomInteger(windowSizeX);
	}


	void GameSettingsHandler::setWindowSizeY(GLint windowSizeY)
	{
		mWindowSizeY.setCustomInteger(windowSizeY);
	}


	void GameSettingsHandler::setWindowPositionX(GLint windowPositionX)
	{
		mWindowPositionX.setCustomInteger(windowPositionX);
	}


	void GameSettingsHandler::setWindowPositionY(GLint windowPositionY)
	{
		mWindowPositionY.setCustomInteger(windowPositionY);
	}
}