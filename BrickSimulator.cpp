#include "FileLocation.h"
#include "BrickSimulator.h"
#include <iostream>

namespace Bountive
{
	const GLint BrickSimulator::TICKS_PER_SECOND = 60;
	const GLfloat BrickSimulator::TIME_SLICE = 1.0f / static_cast<GLfloat>(TICKS_PER_SECOND);
	const GLfloat BrickSimulator::LAG_CAP = 0.15f;

	BrickSimulator::BrickSimulator()
	try : mFileUtil(FileUtil::init()), mWindowHandle(new Window())
	{
		
	}
	catch (std::string e)
	{
		delete mWindowHandle;
		throw(std::string("[BrickSimulator] Could not create BrickSimulator. " + e));
	}


	BrickSimulator::~BrickSimulator()
	{
		std::cout << "Deleting BrickSimulator" << std::endl;
		delete mWindowHandle;
		delete mFileUtil;
	}


	void BrickSimulator::start()
	{
		std::wcout << L"Directory: " << mFileUtil->getmAppdataDir()->getDirectory() << std::endl;
		//TODO: Create a ScreenManager class and set the screen
		loop();
	}


	void BrickSimulator::loop()
	{
		GLdouble mLastTime = glfwGetTime();
		GLdouble mCurrentTime = 0.0f;
		GLdouble mDeltaTime = 0.0f;
		GLdouble mAccumulatedTime = 0.0f;
		
		//TODO: Implement settings to get vsync and other window properties
		glfwSwapInterval(0);

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
			//std::cout << "Ticks: " << mTickCount << " | Frames: " << mFramesPerSecond << std::endl;
			mTickCount = 0;
			mFramesPerSecond = 0;
		}
	}


	void BrickSimulator::render()
	{
		++mFramesPerSecond;

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(mWindowHandle->getWindowHandle());
	}
}