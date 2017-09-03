#include <glew.h>
#include "BrickSimulator.h"
#include "CallbackManager.h"
#include "KeyboardCallback.h"
#include "WindowFocusCallback.h"
#include "FramebufferSizeCallback.h"
#include "WindowSizeCallback.h"
#include "WindowPositionCallback.h"
#include "CursorPositionCallback.h"
#include "MouseScrollCallback.h"
#include "FileSettingsHandler.h"
#include "Logger.h"
#include "LoggerUtil.h"

namespace Bountive
{
	Logger CallbackManager::logger = Logger("CallbackManager", Logger::Level::LEVEL_ALL);

	CallbackManager::CallbackManager(FileSettingsHandler& fileSettingsHandler) :
		mWindowHandle(BrickSimulator::instance->getWindow()->getWindowHandle()),
		mKeyboardCallback(KeyboardCallback::init(*BrickSimulator::instance->getInputTracker(), fileSettingsHandler)),
		mWindowFocusCallback(WindowFocusCallback::init()),
		mWindowSizeCallback(WindowSizeCallback::init(*BrickSimulator::instance->getWindow(), fileSettingsHandler)),
		mFramebufferSizeCallback(FramebufferSizeCallback::init()),
		mWindowPositionCallback(WindowPositionCallback::init(fileSettingsHandler)),
		mCursorPositionCallback(CursorPositionCallback::init(*BrickSimulator::instance->getInputTracker())),
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