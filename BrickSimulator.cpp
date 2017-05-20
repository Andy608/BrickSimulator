#include <glew.h>
#include <log4cxx\helpers\exception.h>
#include "DirectoryUtil.h"
#include "BrickSimulator.h"
#include "Window.h"
#include "GameSettingsHandler.h"
#include "BrickSimulator.h"
#include "FileLocation.h"
#include "Logger.h"
#include "LoggerUtil.h"
#include "SceneManager.h"

namespace Bountive
{
	BrickSimulator* BrickSimulator::instance = nullptr;
	Logger BrickSimulator::logger = Logger("BrickSimulator", Logger::Level::LEVEL_ALL);
	const GLint BrickSimulator::TICKS_PER_SECOND = 60;
	const GLfloat BrickSimulator::TIME_SLICE = 1.0f / static_cast<GLfloat>(TICKS_PER_SECOND);
	const GLfloat BrickSimulator::LAG_CAP = 0.15f;

	BrickSimulator* BrickSimulator::init()
	{
		if (instance == nullptr)
		{
			LoggerUtil::init();
			LoggerUtil::initConsoleAppender();
			DirectoryUtil::init();
			LoggerUtil::initFileAppender();
			logger.log(Logger::Level::LEVEL_INFO, "Initializing BrickSimulator by Andy608...");
			instance = new BrickSimulator();
		}

		return instance;
	}


	BrickSimulator::BrickSimulator()
	try : 
		mDIRECTORY_UTIL(DirectoryUtil::instance),
		mLOGGER_UTIL(LoggerUtil::instance),
		mWindow(new Window()),
		mGameSettingsHandler(new GameSettingsHandler(*mWindow))
	{
		mGameSettingsHandler->updateSettings();
		mWindow->buildWindow(*mGameSettingsHandler);
	}
	catch (std::wstring e)
	{
		throw(std::wstring(L"Could not create BrickSimulator. " + e));
	}
	catch (log4cxx::helpers::Exception& e)
	{
		throw (e);
	}


	BrickSimulator::~BrickSimulator()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting BrickSimulator...");
		delete mDIRECTORY_UTIL;
		delete mLOGGER_UTIL;
		delete mWindow;
		delete mGameSettingsHandler;
	}


	void BrickSimulator::start()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Directory: " + mDIRECTORY_UTIL->mAPPDATA_DIRECTORY->getDirectory());
		loop();
		saveSettings();
	}


	void BrickSimulator::loop()
	{
		GLdouble mLastTime = glfwGetTime();
		GLdouble mCurrentTime = 0.0f;
		GLdouble mDeltaTime = 0.0f;
		GLdouble mAccumulatedTime = 0.0f;

		while (!glfwWindowShouldClose(mWindow->getWindowHandle()))
		{
			mCurrentTime = glfwGetTime();
			mDeltaTime = mCurrentTime - mLastTime;
			mLastTime = mCurrentTime;
			mAccumulatedTime += mDeltaTime;

			if (mAccumulatedTime >= LAG_CAP)
			{
				mAccumulatedTime = LAG_CAP;
			}

			while (mAccumulatedTime > TIME_SLICE)
			{
				mAccumulatedTime -= TIME_SLICE;
				glfwPollEvents();
				update(mDeltaTime);
			}

			render(mDeltaTime);
		}
	}


	void BrickSimulator::update(const GLdouble& DELTA_TIME)
	{
		++mTickCount;

		if (mTickCount % TICKS_PER_SECOND == 0)
		{
			logger.log(Logger::Level::LEVEL_TRACE,
				"Ticks: " + std::to_string(mTickCount) + " | Frames: " + std::to_string(mFramesPerSecond));

			mTickCount = 0;
			mFramesPerSecond = 0;
		}

		mWindow->update(DELTA_TIME);
	}


	void BrickSimulator::render(const GLdouble& DELTA_TIME)
	{
		++mFramesPerSecond;

		mWindow->render(DELTA_TIME);
		glfwSwapBuffers(mWindow->getWindowHandle());
	}


	void BrickSimulator::saveSettings() const
	{
		logger.log(Logger::Level::LEVEL_INFO, "Saving settings to file...");
		mGameSettingsHandler->saveOptionsToFile();
	}
}