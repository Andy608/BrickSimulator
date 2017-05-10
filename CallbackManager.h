#pragma once
#ifndef BOUNTIVE_CALLBACKMANAGER_H_
#define BOUNTIVE_CALLBACKMANAGER_H_

#include "KeyboardCallback.h"
#include "WindowFocusCallback.h"
#include "FramebufferSizeCallback.h"
#include "WindowSizeCallback.h"
#include "WindowPositionCallback.h"
#include "CursorPositionCallback.h"
#include "MouseScrollCallback.h"

namespace Bountive
{
	class CallbackManager
	{
	public:
		CallbackManager(GLFWwindow* windowHandle);
		~CallbackManager();

		static void errorCallback(GLint error, const GLchar* description);

	private:
		GLFWwindow* mWindowHandle;
		KeyboardCallback* mKeyboardCallback;
		WindowFocusCallback* mWindowFocusCallback;
		FramebufferSizeCallback* mFramebufferSizeCallback;
		WindowSizeCallback* mWindowSizeCallback;
		WindowPositionCallback* mWindowPositionCallback;
		CursorPositionCallback* mCursorPositionCallback;
		MouseScrollCallback* mMouseScrollCallback;
	};
}

#endif