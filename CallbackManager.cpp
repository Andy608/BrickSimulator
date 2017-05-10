#include "CallbackManager.h"
#include  <iostream>

namespace Bountive
{
	CallbackManager::CallbackManager(GLFWwindow* windowHandle) :
		mWindowHandle(windowHandle), 
		mKeyboardCallback(KeyboardCallback::init()),
		mWindowFocusCallback(WindowFocusCallback::init()),
		mWindowSizeCallback(WindowSizeCallback::init()),
		mFramebufferSizeCallback(FramebufferSizeCallback::init()),
		mWindowPositionCallback(WindowPositionCallback::init()),
		mCursorPositionCallback(CursorPositionCallback::init()),
		mMouseScrollCallback(MouseScrollCallback::init())
	{
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
		std::cout << "Deleting Window Callbacks." << std::endl;
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
		std::cout << "Error #" << error << ": " << description << std::endl;
	}
}