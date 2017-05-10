#pragma once
#ifndef BOUNTIVE_FRAMEBUFFERSIZECALLBACK_H_
#define BOUNTIVE_FRAMEBUFFERSIZECALLBACK_H_

#include <glew.h>
#include <glfw\glfw3.h>

namespace Bountive
{
	class FramebufferSizeCallback
	{
	public:
		static FramebufferSizeCallback* instance;

		static FramebufferSizeCallback* init();
		static void framebufferSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight);

		~FramebufferSizeCallback();

	private:
		FramebufferSizeCallback();
	};
}

#endif