#include <glew.h>
#include <iostream>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include "DirectoryUtil.h"
#include "BrickSimulator.h"
#include "Window.h"
#include "GameSettingsHandler.h"
#include "InputHandler.h"
#include "BrickSimulator.h"
#include "FileLocation.h"

namespace Bountive
{
	BrickSimulator* BrickSimulator::instance = nullptr;
	log4cxx::LoggerPtr BrickSimulator::brickSimulatorLogger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("brickSimulatorLogger"));

	const GLint BrickSimulator::TICKS_PER_SECOND = 60;
	const GLfloat BrickSimulator::TIME_SLICE = 1.0f / static_cast<GLfloat>(TICKS_PER_SECOND);
	const GLfloat BrickSimulator::LAG_CAP = 0.15f;

	BrickSimulator* BrickSimulator::init()
	{
		if (instance == nullptr)
		{
			std::wcout << "Creating BrickSimulator by Andy608..." << std::endl;
			instance = new BrickSimulator();
		}

		return instance;
	}


	BrickSimulator::BrickSimulator()
	try : 
		mDIRECTORY_UTIL(DirectoryUtil::init()),
		mWindowHandle(Window::init()),
		mGameSettingsHandler(new GameSettingsHandler()),
		mInputHandler(new InputHandler())
	{
		FileDirectory dir = FileDirectory(mDIRECTORY_UTIL->getmAppdataDir()->getDirectory(), L"logger");
		FileLocation loggerProperties = FileLocation(&dir, L"logger", FileLocation::TXT_EXT);
		log4cxx::PropertyConfigurator::configure(loggerProperties.getFullPath());
		LOG4CXX_DEBUG(brickSimulatorLogger, "Entering application...");

		mGameSettingsHandler->updateSettings();
		mWindowHandle->buildWindow(*mGameSettingsHandler);
	}
	catch (std::wstring e)
	{
		delete mDIRECTORY_UTIL;
		delete mWindowHandle;
		delete mGameSettingsHandler;
		delete mInputHandler;
		throw(std::wstring(L"[BrickSimulator] Could not create BrickSimulator. " + e));
	}
	catch (log4cxx::helpers::Exception&)
	{
		delete mDIRECTORY_UTIL;
		delete mWindowHandle;
		delete mGameSettingsHandler;
		delete mInputHandler;
		throw(std::wstring(L"[BrickSimulator] Could not create BrickSimulator due to logger error. "));
	}


	BrickSimulator::~BrickSimulator()
	{
		std::cout << "Deleting BrickSimulator" << std::endl;
		delete mDIRECTORY_UTIL;
		delete mWindowHandle;
		delete mGameSettingsHandler;
		delete mInputHandler;
	}


	void BrickSimulator::start()
	{
		std::wcout << L"Directory: " << mDIRECTORY_UTIL->getmAppdataDir()->getDirectory() << std::endl;
		//TODO: Create a ScreenManager class and set the screen
		loop();
		saveSettings();
		LOG4CXX_INFO(brickSimulatorLogger, "Exited application!");
	}


	void BrickSimulator::loop()
	{
		GLdouble mLastTime = glfwGetTime();
		GLdouble mCurrentTime = 0.0f;
		GLdouble mDeltaTime = 0.0f;
		GLdouble mAccumulatedTime = 0.0f;

		while (!glfwWindowShouldClose(mWindowHandle->getWindowHandle()))
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
				update();
			}

			render();
		}
	}


	void BrickSimulator::update()
	{
		++mTickCount;

		if (mTickCount % TICKS_PER_SECOND == 0)
		{
			std::cout << "Ticks: " << mTickCount << " | Frames: " << mFramesPerSecond << std::endl;
			mTickCount = 0;
			mFramesPerSecond = 0;
		}

		mInputHandler->update();
	}


	void BrickSimulator::render()
	{
		++mFramesPerSecond;

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(mWindowHandle->getWindowHandle());
	}


	void BrickSimulator::saveSettings() const
	{
		std::wcout << "SAVING GAME SETTINGS..." << std::endl;
		mGameSettingsHandler->saveOptionsToFile();
	}
}