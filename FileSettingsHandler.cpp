#include "FileSettingsHandler.h"
#include "DirectoryUtil.h"
#include "FileLocation.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Window.h"
#include "RenderManager.h"
#include "GraphicsOptions.h"
#include "Logger.h"

namespace Bountive
{
	Logger FileSettingsHandler::logger = Logger("FileSettingsHandler", Logger::Level::LEVEL_ALL);
	const std::wstring FileSettingsHandler::SETTINGS_FILE_NAME = L"options";

	FileSettingsHandler::FileSettingsHandler(const Window& window)
		try : 
		mSETTINGS_DIRECTORY(DirectoryUtil::instance->mUSER_CONFIG),
		mSettingsFile(new FileLocation(mSETTINGS_DIRECTORY, SETTINGS_FILE_NAME, FileLocation::TXT_EXTENSION)),
		mFileWriter(new FileWriter()),
		mFileReader(new FileReader()),
		mSaveWindowState(BooleanSetting("save_window_state", GL_FALSE)),
		mWindowMaximized(BooleanSetting("window_maximized", GL_FALSE)),

		mDEFAULT_WINDOW_SIZE(glm::vec2(window.mVIDEO_MODE->width / 2.0f, window.mVIDEO_MODE->height / 2.0f)),

		mDEFAULT_WINDOW_POSITION(glm::vec2((window.mVIDEO_MODE->width - mDEFAULT_WINDOW_SIZE.x) / 2.0f,
			(window.mVIDEO_MODE->height - mDEFAULT_WINDOW_SIZE.y) / 2.0f)),

		mWindowPositionX(ClampedIntegerSetting("window_position_x", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.x), 
			static_cast<GLint>(window.getMinimumWindowPosition().x),
			static_cast<GLint>(window.getMaximumWindowPosition().x))),

		mWindowPositionY(ClampedIntegerSetting("window_position_y", static_cast<GLint>(mDEFAULT_WINDOW_POSITION.y), 
			static_cast<GLint>(window.getMinimumWindowPosition().y),
			static_cast<GLint>(window.getMaximumWindowPosition().y))),

		mWindowSizeX(ClampedIntegerSetting("window_size_x", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.x), 
			static_cast<GLint>(window.mMINIMUM_SIZE_X), static_cast<GLint>(window.mMAXIMUM_SIZE_X))),

		mWindowSizeY(ClampedIntegerSetting("window_size_y", static_cast<GLint>(mDEFAULT_WINDOW_SIZE.y), 
			static_cast<GLint>(window.mMINIMUM_SIZE_Y), static_cast<GLint>(window.mMAXIMUM_SIZE_Y))),

		mVsyncEnabled(new BooleanSetting("vsync", GL_TRUE)),
		mFullscreenEnabled(new BooleanSetting("fullscreen", GL_FALSE)),
		mProjectionID(new ClampedIntegerSetting("projection_id",
			static_cast<GLint>(EnumProjection::PERSPECTIVE), 
			static_cast<GLint>(EnumProjection::PERSPECTIVE), 
			static_cast<GLint>(EnumProjection::ORTHO))),
		mFieldOfView(new ClampedIntegerSetting("fov", 67, 30, 120)),
		mPauseKeyCode(new SingleKeySetting("key_pause", GLFW_KEY_ESCAPE)),
		mCameraForwardKeyCode(new SingleKeySetting("camera_forward", GLFW_KEY_W)),
		mCameraBackwardKeyCode(new SingleKeySetting("camera_backward", GLFW_KEY_S)),
		mCameraLeftKeyCode(new SingleKeySetting("camera_left", GLFW_KEY_A)),
		mCameraRightKeyCode(new SingleKeySetting("camera_right", GLFW_KEY_D)),
		mCameraUpKeyCode(new SingleKeySetting("camera_up", GLFW_KEY_SPACE)),
		mCameraDownKeyCode(new SingleKeySetting("camera_down", GLFW_KEY_LEFT_SHIFT))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating FileSettingsHandler...");
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


	FileSettingsHandler::~FileSettingsHandler()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting FileSettingsHandler.");
		delete mSettingsFile;
		delete mFileWriter;
		delete mFileReader;

		delete mVsyncEnabled;
		delete mFullscreenEnabled;
		delete mProjectionID;
		delete mFieldOfView;
		delete mPauseKeyCode;
		delete mCameraForwardKeyCode;
		delete mCameraBackwardKeyCode;
		delete mCameraLeftKeyCode;
		delete mCameraRightKeyCode;
		delete mCameraUpKeyCode;
		delete mCameraDownKeyCode;
	}


	void FileSettingsHandler::updateSettings()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Loading game options from the settings file...");

		if (mSettingsFile->isCreated())
		{
			loadOptionsFromFile();

			if (mSaveWindowState.getCustomBoolean())
			{
				checkToResetInvalidWindow();
			}
		}
	}


	void FileSettingsHandler::loadOptionsFromFile()
	{
		std::vector<std::string> lines = mFileReader->getLinesInFile(*mSettingsFile);

		for (GLuint i = 0; i < lines.size(); ++i)
		{
			std::string line = lines.at(i);
			for (GLuint j = 0; j < line.length(); ++j)
			{
				if (line.c_str()[j] == SettingType::DELIMITER)
				{
					std::string settingName = line.substr(0, j);
					std::string settingVar = line.substr(j + 1);
					logger.log(Logger::Level::LEVEL_DEBUG, settingName + "=" + settingVar);

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
					else if (settingName.compare(mFullscreenEnabled->getSettingName()) == 0)
					{
						mFullscreenEnabled->setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mVsyncEnabled->getSettingName()) == 0)
					{
						mVsyncEnabled->setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mProjectionID->getSettingName()) == 0)
					{
						mProjectionID->IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mFieldOfView->getSettingName()) == 0)
					{
						mFieldOfView->IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mPauseKeyCode->getSettingName()) == 0)
					{
						mPauseKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraForwardKeyCode->getSettingName()) == 0)
					{
						mCameraForwardKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraBackwardKeyCode->getSettingName()) == 0)
					{
						mCameraBackwardKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraLeftKeyCode->getSettingName()) == 0)
					{
						mCameraLeftKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraRightKeyCode->getSettingName()) == 0)
					{
						mCameraRightKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraUpKeyCode->getSettingName()) == 0)
					{
						mCameraUpKeyCode->setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraDownKeyCode->getSettingName()) == 0)
					{
						mCameraDownKeyCode->setCustomInteger(settingVar);
					}
					else
					{
						logger.log(Logger::Level::LEVEL_WARN, "Skipping unknown setting: \'" + settingName + "\'.");
					}
				}
			}
		}
	}


	void FileSettingsHandler::saveOptionsToFile()
	{
		std::vector<std::string> settingsFile;

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

		settingsFile.push_back(mFullscreenEnabled->toFileString());
		settingsFile.push_back(mVsyncEnabled->toFileString());
		settingsFile.push_back(mProjectionID->toFileString());
		
		settingsFile.push_back(mFieldOfView->toFileString());

		settingsFile.push_back(mPauseKeyCode->toFileString());

		settingsFile.push_back(mCameraForwardKeyCode->toFileString());
		settingsFile.push_back(mCameraBackwardKeyCode->toFileString());
		settingsFile.push_back(mCameraLeftKeyCode->toFileString());
		settingsFile.push_back(mCameraRightKeyCode->toFileString());
		settingsFile.push_back(mCameraUpKeyCode->toFileString());
		settingsFile.push_back(mCameraDownKeyCode->toFileString());

		mFileWriter->writeLinesInFile(*mSettingsFile, settingsFile);
	}


	void FileSettingsHandler::setDefaultSettings()
	{
		mSaveWindowState.resetCustomValue();
		mWindowMaximized.resetCustomValue();
		setDefaultWindowState();

		mFullscreenEnabled->resetCustomValue();
		mVsyncEnabled->resetCustomValue();
		mProjectionID->resetCustomValue();

		mFieldOfView->resetCustomValue();

		mPauseKeyCode->resetCustomValue();

		mCameraForwardKeyCode->resetCustomValue();
		mCameraBackwardKeyCode->resetCustomValue();
		mCameraLeftKeyCode->resetCustomValue();
		mCameraRightKeyCode->resetCustomValue();
		mCameraUpKeyCode->resetCustomValue();
		mCameraDownKeyCode->resetCustomValue();
	}


	void FileSettingsHandler::setDefaultWindowState()
	{
		mWindowMaximized.resetCustomValue();
		mWindowPositionX.resetCustomValue();
		mWindowPositionY.resetCustomValue();
		mWindowSizeX.resetCustomValue();
		mWindowSizeY.resetCustomValue();
	}


	void FileSettingsHandler::setWindowInBounds()
	{
		if (mWindowPositionX.getCustomInteger() <= mWindowPositionX.getMinInteger())
		{
			mWindowPositionX.setCustomInteger(mWindowPositionX.getMinInteger());
		}
		else if (mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() > mWindowPositionX.getMaxInteger())
		{
			mWindowPositionX.setCustomInteger(-mWindowSizeX.getCustomInteger() + mWindowPositionX.getMaxInteger());
		}

		if (mWindowPositionY.getCustomInteger() <= mWindowPositionY.getMinInteger())
		{
			mWindowPositionY.setCustomInteger(mWindowPositionY.getMinInteger());
		}
		else if (mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() > mWindowPositionY.getMaxInteger())
		{
			mWindowPositionY.setCustomInteger(-mWindowSizeY.getCustomInteger() + mWindowPositionY.getMaxInteger());
		}
	}


	void FileSettingsHandler::checkToResetInvalidWindow()
	{
		if ((mWindowPositionX.getCustomInteger() <= mWindowPositionX.getMinInteger())
			|| (mWindowPositionX.getCustomInteger() + mWindowSizeX.getCustomInteger() > mWindowPositionX.getMaxInteger())
			|| (mWindowPositionY.getCustomInteger() <= mWindowPositionY.getMinInteger())
			|| (mWindowPositionY.getCustomInteger() + mWindowSizeY.getCustomInteger() > mWindowPositionY.getMaxInteger()))
		{
			setDefaultWindowState();
		}
	}


	const BooleanSetting& FileSettingsHandler::isSaveWindowState() const
	{
		return mSaveWindowState;
	}


	const BooleanSetting& FileSettingsHandler::isWindowMaximized() const
	{
		return mWindowMaximized;
	}


	const ClampedIntegerSetting& FileSettingsHandler::getWindowWidth() const
	{
		return mWindowSizeX;
	}


	const ClampedIntegerSetting& FileSettingsHandler::getWindowHeight() const
	{
		return mWindowSizeY;
	}

	const ClampedIntegerSetting& FileSettingsHandler::getWindowPositionX() const
	{
		return mWindowPositionX;
	}


	const ClampedIntegerSetting& FileSettingsHandler::getWindowPositionY() const
	{
		return mWindowPositionY;
	}


	BooleanSetting* FileSettingsHandler::isVsyncEnabled() const
	{
		return mVsyncEnabled;
	}


	BooleanSetting* FileSettingsHandler::isFullscreenEnabled() const
	{
		return mFullscreenEnabled;
	}


	ClampedIntegerSetting* FileSettingsHandler::getProjectionID() const
	{
		return mProjectionID;
	}


	ClampedIntegerSetting* FileSettingsHandler::getFieldOfView() const
	{
		return mFieldOfView;
	}


	SingleKeySetting* FileSettingsHandler::getPauseKeyCode() const
	{
		return mPauseKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraForwardKeyCode() const
	{
		return mCameraForwardKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraBackwardKeyCode() const
	{
		return mCameraBackwardKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraLeftKeyCode() const
	{
		return mCameraLeftKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraRightKeyCode() const
	{
		return mCameraRightKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraUpKeyCode() const
	{
		return mCameraUpKeyCode;
	}


	SingleKeySetting* FileSettingsHandler::getCameraDownKeyCode() const
	{
		return mCameraDownKeyCode;
	}


	void FileSettingsHandler::setSaveWindowState(GLboolean saveWindowState)
	{
		mSaveWindowState.setCustomBoolean(saveWindowState);
	}


	void FileSettingsHandler::setWindowMaximized(GLboolean windowMaximized)
	{
		mWindowMaximized.setCustomBoolean(windowMaximized);
	}


	void FileSettingsHandler::setWindowSizeX(GLint windowSizeX)
	{
		mWindowSizeX.setCustomInteger(windowSizeX);
	}


	void FileSettingsHandler::setWindowSizeY(GLint windowSizeY)
	{
		mWindowSizeY.setCustomInteger(windowSizeY);
	}


	void FileSettingsHandler::setWindowPositionX(GLint windowPositionX)
	{
		mWindowPositionX.setCustomInteger(windowPositionX);
	}


	void FileSettingsHandler::setWindowPositionY(GLint windowPositionY)
	{
		mWindowPositionY.setCustomInteger(windowPositionY);
	}


	void FileSettingsHandler::setVsyncEnabled(GLboolean vsyncEnabled)
	{
		mVsyncEnabled->setCustomBoolean(vsyncEnabled);
	}


	void FileSettingsHandler::setFullscreenEnabled(GLboolean fullscreenEnabled)
	{
		mFullscreenEnabled->setCustomBoolean(fullscreenEnabled);
	}


	void FileSettingsHandler::setProjectionID(const EnumProjection& projectionType)
	{
		mProjectionID->setCustomInteger(static_cast<GLint>(projectionType));
	}


	void FileSettingsHandler::setFieldOfView(GLint fieldOfView)
	{
		mFieldOfView->setCustomInteger(fieldOfView);
	}
}