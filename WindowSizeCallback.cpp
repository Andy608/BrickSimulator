#include "WindowSizeCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	WindowSizeCallback* WindowSizeCallback::instance = nullptr;
	Logger WindowSizeCallback::logger = Logger("WindowSizeCallback", Logger::Level::LEVEL_ALL);

	WindowSizeCallback* WindowSizeCallback::init(const Window& window, FileSettingsHandler& fileSettingsHandler)
	{
		if (instance == nullptr)
		{
			instance = new WindowSizeCallback(window, fileSettingsHandler);
		}

		return instance;
	}


	WindowSizeCallback::WindowSizeCallback(const Window& window, FileSettingsHandler& fileSettingsHandler) :
		mWindow(window),
		mFileSettingsHandler(fileSettingsHandler),
		mWindowSize(fileSettingsHandler.getWindowWidth().getCustomInteger(), fileSettingsHandler.getWindowHeight().getCustomInteger()),
		mWindowCenter(mWindowSize / 2.0f)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating WindowSizeCallback...");
	}


	WindowSizeCallback::~WindowSizeCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting WindowSizeCallback...");
	}


	void WindowSizeCallback::windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		instance->mWindowSize.x = static_cast<GLfloat>(windowWidth);
		instance->mWindowSize.y = static_cast<GLfloat>(windowHeight);
		instance->mWindowCenter = instance->mWindowSize / 2.0f;

		if (instance->mWindow.mMAXIMUM_SIZE_X == windowWidth
			&& instance->mWindow.mMAXIMUM_SIZE_Y - (instance->mWindow.mMAXIMUM_SIZE_Y / 8) < windowHeight)
		{
			instance->mFileSettingsHandler.setWindowMaximized(GL_TRUE);
			instance->mFileSettingsHandler.setDefaultWindowState();
		}
		else
		{
			instance->mFileSettingsHandler.setWindowMaximized(GL_FALSE);
			instance->mFileSettingsHandler.setWindowSizeX(windowWidth);
			instance->mFileSettingsHandler.setWindowSizeY(windowHeight);
		}
	}


	const glm::vec2& WindowSizeCallback::getWindowSize() const
	{
		return mWindowSize;
	}


	const glm::vec2& WindowSizeCallback::getWindowCenter() const
	{
		return mWindowCenter;
	}
}