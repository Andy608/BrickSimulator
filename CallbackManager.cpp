#include <glew.h>
#include "CallbackManager.h"
#include "KeyboardCallback.h"
#include "WindowFocusCallback.h"
#include "FramebufferSizeCallback.h"
#include "WindowSizeCallback.h"
#include "WindowPositionCallback.h"
#include "CursorPositionCallback.h"
#include "MouseScrollCallback.h"
#include "Window.h"
#include "GameSettingsHandler.h"
#include "Logger.h"
#include "LoggerUtil.h"

namespace Bountive
{
	Logger CallbackManager::logger = Logger("CallbackManager", Logger::Level::LEVEL_ALL);

	CallbackManager::CallbackManager(const Window& window, GameSettingsHandler& gameSettingsHandler) :
		mWindowHandle(window.getWindowHandle()),
		mKeyboardCallback(KeyboardCallback::init(window, gameSettingsHandler)),
		mWindowFocusCallback(WindowFocusCallback::init()),
		mWindowSizeCallback(WindowSizeCallback::init(window, gameSettingsHandler)),
		mFramebufferSizeCallback(FramebufferSizeCallback::init()),
		mWindowPositionCallback(WindowPositionCallback::init(gameSettingsHandler)),
		mCursorPositionCallback(CursorPositionCallback::init()),
		mMouseScrollCallback(MouseScrollCallback::init())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating CallbackManager...");
		glfwSetErrorCallback(errorCallback);
		glfwSetKeyCallback(mWindowHandle, mKeyboardCallback->keyCallback);
		glfwSetWindowFocusCallback(mWindowHandle, mWindowFocusCallback->windowFocusCallback);
		glfwSetFramebufferSizeCallback(mWindowHandle, mFramebufferSizeCallback->framebufferSizeCallback);
		glfwSetWindowSizeCallback(mWindowHandle, mWindowSizeCallback->windowSizeCallback);
		glfwSetWindowPosCallback(mWindowHandle, mWindowPositionCallback->windowPositionCallback);
		glfwSetCursorPosCallback(mWindowHandle, mCursorPositionCallback->cursorPositionCallback);
		glfwSetScrollCallback(mWindowHandle, mMouseScrollCallback->mouseScrollCallback);
	}


	CallbackManager::~CallbackManager()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting CallbackManager...");
		delete mKeyboardCallback;
		delete mWindowFocusCallback;
		delete mFramebufferSizeCallback;
		delete mWindowSizeCallback;
		delete mWindowPositionCallback;
		delete mCursorPositionCallback;
		delete mMouseScrollCallback;
	}


	void CallbackManager::errorCallback(GLint error, const GLchar* description)
	{
		logger.log(Logger::Level::LEVEL_ERROR, "#" + std::to_string(error) + ": " + description);
	}
}