#include "FramebufferSizeCallback.h"
#include <iostream>

namespace Bountive
{
	FramebufferSizeCallback* FramebufferSizeCallback::instance = nullptr;

	FramebufferSizeCallback* FramebufferSizeCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new FramebufferSizeCallback();
		}

		return instance;
	}


	FramebufferSizeCallback::FramebufferSizeCallback() {}


	FramebufferSizeCallback::~FramebufferSizeCallback()
	{
		std::cout << "Deleting FramebufferSizeCallback." << std::endl;
	}


	void FramebufferSizeCallback::framebufferSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		std::cout << "Framebuffer Width: " << windowWidth << " | Framebuffer Height: " << windowHeight << std::endl;
		glViewport(0, 0, windowWidth, windowHeight);
	}
}