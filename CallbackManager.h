#pragma once
#ifndef BOUNTIVE_CALLBACKMANAGER_H_
#define BOUNTIVE_CALLBACKMANAGER_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class KeyboardCallback;
	class WindowFocusCallback;
	class FramebufferSizeCallback;
	class WindowSizeCallback;
	class WindowPositionCallback;
	class CursorPositionCallback;
	class MouseScrollCallback;
	class FileSettingsHandler;
	class Logger;

	class CallbackManager
	{
	public:
		static void errorCallback(GLint error, const GLchar* description);

		CallbackManager(FileSettingsHandler& fileSettingsHandler);
		~CallbackManager();

		GLFWwindow* mWindowHandle;
		KeyboardCallback* mKeyboardCallback;
		WindowFocusCallback* mWindowFocusCallback;
		WindowSizeCallback* mWindowSizeCallback;
		FramebufferSizeCallback* mFramebufferSizeCallback;
		WindowPositionCallback* mWindowPositionCallback;
		CursorPositionCallback* mCursorPositionCallback;
		MouseScrollCallback* mMouseScrollCallback;

	private:
		static Logger logger;
	};
}

#endif