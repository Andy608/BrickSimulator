#include <glew.h>
#include <iostream>
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

namespace Bountive
{
	CallbackManager::CallbackManager(Window* window, GameSettingsHandler& gameSettingsHandler) :
		mWindowHandle(window->getWindowHandle()),
		mKeyboardCallback(KeyboardCallback::init(gameSettingsHandler)),
		mWindowFocusCallback(WindowFocusCallback::init()),
		mWindowSizeCallback(WindowSizeCallback::init(gameSettingsHandler)),
		mFramebufferSizeCallback(FramebufferSizeCallback::init()),
		mWindowPositionCallback(WindowPositionCallback::init(gameSettingsHandler)),
		mCursorPositionCallback(CursorPositionCallback::init()),
		mMouseScrollCallback(MouseScrollCallback::init())
	{
		glfwSetErrorCallback(errorCallback);
		glfwSetKeyCallback(mWindowHandle, mKeyboardCallback->keyCallback);
		glfwSetWindowFocusCallback(mWindowHandle, mWindowFocusCallback->windowFocusCallback);
		glfwSetWindowSizeCallback(mWindowHandle, mWindowSizeCallback->windowSizeCallback);
		glfwSetFramebufferSizeCallback(mWindowHandle, mFramebufferSizeCallback->framebufferSizeCallback);
		glfwSetWindowPosCallback(mWindowHandle, mWindowPositionCallback->windowPositionCallback);
		glfwSetCursorPosCallback(mWindowHandle, mCursorPositionCallback->cursorPositionCallback);
		glfwSetScrollCallback(mWindowHandle, mMouseScrollCallback->mouseScrollCallback);
	}


	CallbackManager::~CallbackManager()
	{
		std::cout << "Deleting Window Callbacks." << std::endl;
		delete mKeyboardCallback;
		delete mWindowFocusCallback;
		delete mWindowSizeCallback;
		delete mFramebufferSizeCallback;
		delete mWindowPositionCallback;
		delete mCursorPositionCallback;
		delete mMouseScrollCallback;
	}


	void CallbackManager::errorCallback(GLint error, const GLchar* description)
	{
		std::cout << "Error #" << error << ": " << description << std::endl;
	}
}