#include <glew.h>
#include <log4cxx\helpers\exception.h>
#include "DirectoryUtil.h"
#include "BrickSimulator.h"
#include "Window.h"
#include "FileSettingsHandler.h"
#include "BrickSimulator.h"
#include "FileLocation.h"
#include "Logger.h"
#include "LoggerUtil.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ShaderList.h"
#include "GraphicsOptions.h"

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
			instance->mWindow->buildWindow(*instance->mFileSettingsHandler);
			instance->mRenderManager = new RenderManager();
			instance->mSceneManager = new SceneManager(*instance->mWindow, *instance->mResourceBundleTracker, *instance->mRenderManager);
			RenderManager::updateRenderScreenSize(instance->mFileSettingsHandler->getWindowWidth().getCustomInteger(), instance->mFileSettingsHandler->getWindowHeight().getCustomInteger());
		}

		return instance;
	}


	BrickSimulator::BrickSimulator()
	try : 
		mDIRECTORY_UTIL(DirectoryUtil::instance),
		mLOGGER_UTIL(LoggerUtil::instance),
		mWindow(new Window()),
		mFileSettingsHandler(new FileSettingsHandler(*mWindow)),
		mGraphicsOptions(GraphicsOptions::init(*mFileSettingsHandler)),
		mInputTracker(InputTracker::init(*mFileSettingsHandler)),
		mResourceBundleTracker(new ResourceBundleTracker()),
		mEntityTracker(new EntityTracker())
	{
		mFileSettingsHandler->updateSettings();
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
		delete mSceneManager;
		delete mInputTracker;
		delete mFileSettingsHandler;
		delete mResourceBundleTracker;
		delete mEntityTracker;
		delete mRenderManager;
	}


	void BrickSimulator::start()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Directory: " + mDIRECTORY_UTIL->mAPPDATA->getDirectory());
		loop();
		saveSettings();
	}


	void BrickSimulator::loop()
	{
		GLdouble lastTime = glfwGetTime();
		GLdouble currentTime = 0.0f;
		GLdouble deltaTime = 0.0f;
		GLdouble accumulatedTime = 0.0f;

		while (!glfwWindowShouldClose(mWindow->getWindowHandle()))
		{
			currentTime = glfwGetTime();
			deltaTime = (currentTime - lastTime);
			accumulatedTime += deltaTime;
			lastTime = currentTime;

			if (accumulatedTime >= LAG_CAP)
			{
				accumulatedTime = LAG_CAP;
			}

			while (accumulatedTime > TIME_SLICE)
			{
				accumulatedTime -= TIME_SLICE;
				update(TIME_SLICE);
				glfwPollEvents();
			}

			render(deltaTime);
		}
	}


	void BrickSimulator::update(const GLdouble& DELTA_TIME)
	{
		++mTickCount;

		if (mTickCount % TICKS_PER_SECOND == 0)
		{
			logger.log(Logger::Level::LEVEL_DEBUG,
				"Ticks: " + std::to_string(mTickCount) + " | Frames: " + std::to_string(mFramesPerSecond));

			mTickCount = 0;
			mFramesPerSecond = 0;
		}

		mWindow->update(DELTA_TIME);
		mSceneManager->update(DELTA_TIME);
		mInputTracker->update(DELTA_TIME);
	}


	void BrickSimulator::render(const GLdouble& DELTA_TIME)
	{
		++mFramesPerSecond;

		mSceneManager->render(DELTA_TIME);
		mWindow->render(DELTA_TIME);
		glfwSwapBuffers(mWindow->getWindowHandle());
	}


	void BrickSimulator::saveSettings() const
	{
		logger.log(Logger::Level::LEVEL_INFO, "Saving settings to file...");
		mFileSettingsHandler->saveOptionsToFile();
	}


	Window* BrickSimulator::getWindow() const
	{
		return mWindow;
	}
	

	SceneManager* BrickSimulator::getSceneManager() const
	{
		return mSceneManager;
	}


	InputTracker* BrickSimulator::getInputTracker() const
	{
		return mInputTracker;
	}
}