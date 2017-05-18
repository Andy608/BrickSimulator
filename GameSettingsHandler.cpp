#include <iostream>
#include "GameSettingsHandler.h"
#include "DirectoryUtil.h"
#include "FileLocation.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger GameSettingsHandler::logger = Logger("GameSettingsHandler", Logger::Level::LEVEL_ALL);
	const std::wstring GameSettingsHandler::SETTINGS_FILE_NAME = L"options";

	GameSettingsHandler::GameSettingsHandler()
		try : 
		mSETTINGS_DIRECTORY(DirectoryUtil::instance->mSETTINGS_DIRECTORY),
		mSettingsFile(new FileLocation(mSETTINGS_DIRECTORY, SETTINGS_FILE_NAME, FileLocation::TXT_EXT)),
		mFileWriter(new FileWriter()),
		mFileReader(new FileReader()),
		mSaveWindowState(BooleanSetting(L"save_window_state", GL_FALSE)),
		mWindowMaximized(BooleanSetting(L"window_maximized", GL_FALSE)),

		mDEFAULT_WINDOW_SIZE(glm::vec2(Window::instance->mVIDEO_MODE->width / 2.0f, Window::instance->mVIDEO_MODE->height / 2.0f)),

		mDEFAULT_WINDOW_POSITION(glm::vec2((Window::instance->mVIDEO_MODE->width - mDEFAULT_WINDOW_SIZE.x) / 2.0f, 
			(Window::instance->mVIDEO_MODE->height - mDEFAULT_WINDOW_SIZE.y) / 2.0f)),

		mWindowPositionX(ClampedIntegerSetting(L"window_position_x", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.x), 
			static_cast<GLint>(Window::instance->getMinimumWindowPosition().x),
			static_cast<GLint>(Window::instance->getMaximumWindowPosition().x))),

		mWindowPositionY(ClampedIntegerSetting(L"window_position_y", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.y), 
			static_cast<GLint>(Window::instance->getMinimumWindowPosition().y),
			static_cast<GLint>(Window::instance->getMaximumWindowPosition().y))),

		mWindowSizeX(ClampedIntegerSetting(L"window_size_x", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.x), 
			static_cast<GLint>(Window::instance->mMINIMUM_SIZE_X), static_cast<GLint>(Window::instance->mMAXIMUM_SIZE_X))),

		mWindowSizeY(ClampedIntegerSetting(L"window_size_y", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.y), 
			static_cast<GLint>(Window::instance->mMINIMUM_SIZE_Y), static_cast<GLint>(Window::instance->mMAXIMUM_SIZE_Y))),

		mVsyncEnabled(BooleanSetting(L"vsync", GL_TRUE)),
		mFullscreenEnabled(BooleanSetting(L"fullscreen", GL_FALSE)),
		mFieldOfView(ClampedIntegerSetting(L"fov", 67, 30, 120)),
		mKeyEscape(IntegerSetting(L"key_escape", GLFW_KEY_ESCAPE))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating GameSettingsHandler...");
		mSettingsFile->createFile(mFileWriter->getWriteStream());

		if (mSettingsFile->isCreated())
		{
			logger.log(Logger::Level::LEVEL_INFO, L"Successfully created settings file! : " + mSettingsFile->getFullPath());
		}
		else
		{
			std::wstring error = L"Error creating settings file. : " + mSettingsFile->getFullPath();
			logger.log(Logger::Level::LEVEL_ERROR, error);
			throw (error);
		}
	}
	catch (std::wstring e)
	{
		throw (e);
	}


	GameSettingsHandler::~GameSettingsHandler()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SettingsHandler.");
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
				checkToResetInvalidWindow();
			}
		}
	}


	void GameSettingsHandler::loadOptionsFromFile()
	{
		std::vector<std::wstring> lines = mFileReader->getLinesInFile(*mSettingsFile);

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
					else if (settingName.compare(mWindowMaximized.getSettingName()) == 0)
					{
						mWindowMaximized.setCustomBoolean(settingVar);
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
					else if (settingName.compare(mFullscreenEnabled.getSettingName()) == 0)
					{
						mFullscreenEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mVsyncEnabled.getSettingName()) == 0)
					{
						mVsyncEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mFieldOfView.getSettingName()) == 0)
					{
						mFieldOfView.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mKeyEscape.getSettingName()) == 0)
					{
						mKeyEscape.setCustomInteger(settingVar);
					}
					else
					{
						logger.log(Logger::Level::LEVEL_WARN, L"Skipping unknown setting: \'" + settingName + L"\'.");
					}
				}
			}
		}
	}


	void GameSettingsHandler::saveOptionsToFile()
	{
		std::vector<std::wstring> settingsFile;

		settingsFile.push_back(mSaveWindowState.toFileString());

		if (!mSaveWindowState.getCustomBoolean())
		{
			setDefaultWindowState();
		}

		settingsFile.push_back(mWindowMaximized.toFileString());
		settingsFile.push_back(mWindowPositionX.toFileString());
		settingsFile.push_back(mWindowPositionY.toFileString());
		settingsFile.push_back(mWindowSizeX.toFileString());
		settingsFile.push_back(mWindowSizeY.toFileString());

		settingsFile.push_back(mFullscreenEnabled.toFileString());
		settingsFile.push_back(mVsyncEnabled.toFileString());
		
		settingsFile.push_back(mFieldOfView.toFileString());
		settingsFile.push_back(mKeyEscape.toFileString());

		mFileWriter->writeLinesInFile(*mSettingsFile, settingsFile);
	}


	void GameSettingsHandler::setDefaultSettings()
	{
		mSaveWindowState.resetCustomValue();
		mWindowMaximized.resetCustomValue();
		setDefaultWindowState();

		mFullscreenEnabled.resetCustomValue();
		mVsyncEnabled.resetCustomValue();

		mFieldOfView.resetCustomValue();

		mKeyEscape.resetCustomValue();
	}


	void GameSettingsHandler::setDefaultWindowState()
	{
		mWindowMaximized.resetCustomValue();
		mWindowPositionX.resetCustomValue();
		mWindowPositionY.resetCustomValue();
		mWindowSizeX.resetCustomValue();
		mWindowSizeY.resetCustomValue();
	}


	void GameSettingsHandler::setWindowInBounds()
	{
		if (mWindowPositionX.getCustomInteger() <= mWindowPositionX.getMinInteger())
		{
			mWindowPositionX.setCustomInteger(mWindowPositionX.getMinInteger());
		}
		else if (mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() > mWindowPositionX.getMaxInteger())
		{
			mWindowPositionX.setCustomInteger(-mWindowSizeX.getCustomInteger() + mWindowPositionX.getMaxInteger());
		}

		std::wcout << mWindowPositionY.getCustomInteger() << std::endl;
		if (mWindowPositionY.getCustomInteger() <= mWindowPositionY.getMinInteger())
		{
			mWindowPositionY.setCustomInteger(mWindowPositionY.getMinInteger());
		}
		else if (mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() > mWindowPositionY.getMaxInteger())
		{
			mWindowPositionY.setCustomInteger(-mWindowSizeY.getCustomInteger() + mWindowPositionY.getMaxInteger());
		}
	}


	void GameSettingsHandler::checkToResetInvalidWindow()
	{
		if ((mWindowPositionX.getCustomInteger() <= mWindowPositionX.getMinInteger())
			|| (mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() > mWindowPositionX.getMaxInteger())
			|| (mWindowPositionY.getCustomInteger() <= mWindowPositionY.getMinInteger())
			|| (mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() > mWindowPositionY.getMaxInteger()))
		{
			setDefaultWindowState();
		}
	}


	const BooleanSetting& GameSettingsHandler::isSaveWindowState() const
	{
		return mSaveWindowState;
	}


	const BooleanSetting& GameSettingsHandler::isWindowMaximized() const
	{
		return mWindowMaximized;
	}


	const ClampedIntegerSetting& GameSettingsHandler::getWindowWidth() const
	{
		return mWindowSizeX;
	}


	const ClampedIntegerSetting& GameSettingsHandler::getWindowHeight() const
	{
		return mWindowSizeY;
	}

	const ClampedIntegerSetting& GameSettingsHandler::getWindowPositionX() const
	{
		return mWindowPositionX;
	}


	const ClampedIntegerSetting& GameSettingsHandler::getWindowPositionY() const
	{
		return mWindowPositionY;
	}


	const BooleanSetting& GameSettingsHandler::isVsyncEnabled() const
	{
		return mVsyncEnabled;
	}


	const BooleanSetting& GameSettingsHandler::isFullscreenEnabled() const
	{
		return mFullscreenEnabled;
	}


	const ClampedIntegerSetting& GameSettingsHandler::getFieldOfView() const
	{
		return mFieldOfView;
	}


	const IntegerSetting& GameSettingsHandler::getKeyEscape() const
	{
		return mKeyEscape;
	}


	void GameSettingsHandler::setSaveWindowState(GLboolean saveWindowState)
	{
		mSaveWindowState.setCustomBoolean(saveWindowState);
	}


	void GameSettingsHandler::setWindowMaximized(GLboolean windowMaximized)
	{
		mWindowMaximized.setCustomBoolean(windowMaximized);
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


	void GameSettingsHandler::setVsyncEnabled(GLboolean vsyncEnabled)
	{
		mVsyncEnabled.setCustomBoolean(vsyncEnabled);
	}


	void GameSettingsHandler::setFullscreenEnabled(GLboolean fullscreenEnabled)
	{
		mFullscreenEnabled.setCustomBoolean(fullscreenEnabled);
	}


	void GameSettingsHandler::setFieldOfView(GLint fieldOfView)
	{
		mFieldOfView.setCustomInteger(fieldOfView);
	}
}