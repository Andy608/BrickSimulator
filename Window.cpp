#include "Window.h"
#include <iostream>
#include <string>

namespace Bountive
{
	Window::Window()
	{
		glfwInit();
		mVIDEO_MODE = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		mWindowHandle = glfwCreateWindow(mVIDEO_MODE->width / 2, mVIDEO_MODE->height / 2, "Brick Simulator 2017", nullptr, nullptr);

		if (mWindowHandle == nullptr)
		{
			throw std::string("[Window] Window could not be created.");
		}
		else
		{
			glfwMakeContextCurrent(mWindowHandle);
			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK)
			{
				throw std::string("[Window] GLEW could not be initialized.");
			}

			GLint windowWidth, windowHeight;
			glfwGetFramebufferSize(mWindowHandle, &windowWidth, &windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);
		}

		mCallbackManager = new CallbackManager(mWindowHandle);
	}


	Window::~Window()
	{
		std::cout << "Deleting window" << std::endl;
		delete mCallbackManager;
		glfwTerminate();
	}


	GLFWwindow* Window::getWindowHandle() const
	{
		return mWindowHandle;
	}
}