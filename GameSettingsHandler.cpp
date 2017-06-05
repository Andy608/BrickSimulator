#include "GameSettingsHandler.h"
#include "DirectoryUtil.h"
#include "FileLocation.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Window.h"
#include "RenderManager.h"
#include "Logger.h"

namespace Bountive
{
	Logger GameSettingsHandler::logger = Logger("GameSettingsHandler", Logger::Level::LEVEL_ALL);
	const std::wstring GameSettingsHandler::SETTINGS_FILE_NAME = L"options";

	GameSettingsHandler::GameSettingsHandler(const Window& window)
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

		mVsyncEnabled(BooleanSetting("vsync", GL_TRUE)),
		mFullscreenEnabled(BooleanSetting("fullscreen", GL_FALSE)),
		mPerspectiveProjectionEnabled(BooleanSetting("perspective_projection", GL_TRUE)),
		mFieldOfView(ClampedIntegerSetting("fov", 67, 30, 120)),
		mPauseKeyCode(IntegerSetting("key_pause", GLFW_KEY_ESCAPE)),
		mCameraForwardKeyCode(IntegerSetting("camera_forward", GLFW_KEY_W)),
		mCameraBackwardKeyCode(IntegerSetting("camera_backward", GLFW_KEY_S)),
		mCameraLeftKeyCode(IntegerSetting("camera_left", GLFW_KEY_A)),
		mCameraRightKeyCode(IntegerSetting("camera_right", GLFW_KEY_D)),
		mCameraUpKeyCode(IntegerSetting("camera_up", GLFW_KEY_SPACE)),
		mCameraDownKeyCode(IntegerSetting("camera_down", GLFW_KEY_RIGHT_SHIFT))
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


	void GameSettingsHandler::loadOptionsFromFile()
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
					else if (settingName.compare(mFullscreenEnabled.getSettingName()) == 0)
					{
						mFullscreenEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mVsyncEnabled.getSettingName()) == 0)
					{
						mVsyncEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mPerspectiveProjectionEnabled.getSettingName()) == 0)
					{
						mPerspectiveProjectionEnabled.setCustomBoolean(settingVar);
					}
					else if (settingName.compare(mFieldOfView.getSettingName()) == 0)
					{
						mFieldOfView.IntegerSetting::setCustomInteger(settingVar);
					}
					else if (settingName.compare(mPauseKeyCode.getSettingName()) == 0)
					{
						mPauseKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraForwardKeyCode.getSettingName()) == 0)
					{
						mCameraForwardKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraBackwardKeyCode.getSettingName()) == 0)
					{
						mCameraBackwardKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraLeftKeyCode.getSettingName()) == 0)
					{
						mCameraLeftKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraRightKeyCode.getSettingName()) == 0)
					{
						mCameraRightKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraUpKeyCode.getSettingName()) == 0)
					{
						mCameraUpKeyCode.setCustomInteger(settingVar);
					}
					else if (settingName.compare(mCameraDownKeyCode.getSettingName()) == 0)
					{
						mCameraDownKeyCode.setCustomInteger(settingVar);
					}
					else
					{
						logger.log(Logger::Level::LEVEL_WARN, "Skipping unknown setting: \'" + settingName + "\'.");
					}
				}
			}
		}
	}


	void GameSettingsHandler::saveOptionsToFile()
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

		settingsFile.push_back(mFullscreenEnabled.toFileString());
		settingsFile.push_back(mVsyncEnabled.toFileString());
		settingsFile.push_back(mPerspectiveProjectionEnabled.toFileString());
		
		settingsFile.push_back(mFieldOfView.toFileString());

		settingsFile.push_back(InputTracker::instance->getPauseKey().toFileString());

		settingsFile.push_back(InputTracker::instance->getCameraForwardKey().toFileString());
		settingsFile.push_back(InputTracker::instance->getCameraBackwardKey().toFileString());
		settingsFile.push_back(InputTracker::instance->getCameraLeftKey().toFileString());
		settingsFile.push_back(InputTracker::instance->getCameraRightKey().toFileString());
		settingsFile.push_back(InputTracker::instance->getCameraUpKey().toFileString());
		settingsFile.push_back(InputTracker::instance->getCameraDownKey().toFileString());

		mFileWriter->writeLinesInFile(*mSettingsFile, settingsFile);
	}


	void GameSettingsHandler::setDefaultSettings()
	{
		mSaveWindowState.resetCustomValue();
		mWindowMaximized.resetCustomValue();
		setDefaultWindowState();

		mFullscreenEnabled.resetCustomValue();
		mVsyncEnabled.resetCustomValue();
		mPerspectiveProjectionEnabled.resetCustomValue();

		mFieldOfView.resetCustomValue();

		mPauseKeyCode.resetCustomValue();

		mCameraForwardKeyCode.resetCustomValue();
		mCameraBackwardKeyCode.resetCustomValue();
		mCameraLeftKeyCode.resetCustomValue();
		mCameraRightKeyCode.resetCustomValue();
		mCameraUpKeyCode.resetCustomValue();
		mCameraDownKeyCode.resetCustomValue();
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


	const BooleanSetting& GameSettingsHandler::isPerspectiveProjection() const
	{
		return mPerspectiveProjectionEnabled;
	}


	const ClampedIntegerSetting& GameSettingsHandler::getFieldOfView() const
	{
		return mFieldOfView;
	}


	const IntegerSetting& GameSettingsHandler::getPauseKeyCode() const
	{
		return mPauseKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraForwardKeyCode() const
	{
		return mCameraForwardKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraBackwardKeyCode() const
	{
		return mCameraBackwardKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraLeftKeyCode() const
	{
		return mCameraLeftKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraRightKeyCode() const
	{
		return mCameraRightKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraUpKeyCode() const
	{
		return mCameraUpKeyCode;
	}


	const IntegerSetting& GameSettingsHandler::getCameraDownKeyCode() const
	{
		return mCameraDownKeyCode;
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


	void GameSettingsHandler::setPerspectiveProjectionEnabled(GLboolean perspectiveProjectionEnabled)
	{
		mPerspectiveProjectionEnabled.setCustomBoolean(perspectiveProjectionEnabled);
	}


	void GameSettingsHandler::setFieldOfView(GLint fieldOfView)
	{
		mFieldOfView.setCustomInteger(fieldOfView);
	}
}