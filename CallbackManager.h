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
	class Window;
	class GameSettingsHandler;
	class Logger;

	class CallbackManager
	{
	public:
		static void errorCallback(GLint error, const GLchar* description);

		CallbackManager(Window* window, GameSettingsHandler& gameSettingsHandler);
		~CallbackManager();

	private:
		static Logger logger;

		GLFWwindow* mWindowHandle;
		KeyboardCallback* mKeyboardCallback;
		WindowFocusCallback* mWindowFocusCallback;
		WindowSizeCallback* mWindowSizeCallback;
		FramebufferSizeCallback* mFramebufferSizeCallback;
		WindowPositionCallback* mWindowPositionCallback;
		CursorPositionCallback* mCursorPositionCallback;
		MouseScrollCallback* mMouseScrollCallback;
	};
}

#endif