#pragma once
#ifndef BOUNTIVE_WINDOWSIZECALLBACK_H_
#define BOUNTIVE_WINDOWSIZECALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>
#include <glm\vec2.hpp>
#include <log4cxx\logger.h>
#include "FileSettingsHandler.h"

namespace Bountive
{
	class Window;

	class WindowSizeCallback
	{
	public:
		static WindowSizeCallback* instance;

		static WindowSizeCallback* init(const Window& window, FileSettingsHandler& fileSettingsHandler);
		static void windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight);

		~WindowSizeCallback();

		const glm::vec2& getWindowSize() const;
		const glm::vec2& getWindowCenter() const;

	private:
		static Logger logger;
		
		const Window& mWindow;
		FileSettingsHandler& mFileSettingsHandler;

		glm::vec2 mWindowSize;
		glm::vec2 mWindowCenter;

		WindowSizeCallback(const Window& window, FileSettingsHandler& fileSettingsHandler);
	};
}

#endif