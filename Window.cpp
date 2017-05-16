#include <glm\vec2.hpp>
#include <iostream>
#include <string>
#include "BrickSimulator.h"
#include "CallbackManager.h"
#include "GameSettingsHandler.h"

namespace Bountive
{
	Window* Window::instance = nullptr;
	
	Window* Window::init()
	{
		if (instance == nullptr)
		{
			std::wcout << "Creating Window Wrapper." << std::endl;
			instance = new Window();
		}

		return instance;
	}


	const GLFWvidmode* Window::initGLFW()
	{
		glfwInit();
		return glfwGetVideoMode(glfwGetPrimaryMonitor());
	}

	Window::Window() :
		mVIDEO_MODE(initGLFW()),
		mMINIMUM_SIZE_X(static_cast<GLint>(mVIDEO_MODE->width / 16.0f)),
		mMINIMUM_SIZE_Y(1),
		mMAXIMUM_SIZE_X(mVIDEO_MODE->width),
		mMAXIMUM_SIZE_Y(mVIDEO_MODE->height)
	{

	}


	Window::~Window()
	{
		std::cout << "Deleting window" << std::endl;
		delete mCallbackManager;
		glfwTerminate();
	}


	void Window::buildWindow(GameSettingsHandler& gameSettingsHandler)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		mWindowHandle = glfwCreateWindow(gameSettingsHandler.getWindowWidth(), gameSettingsHandler.getWindowHeight(), "Brick Simulator 2017", nullptr, nullptr);
		glfwHideWindow(mWindowHandle);
		glfwSetWindowPos(mWindowHandle, gameSettingsHandler.getWindowPositionX(), gameSettingsHandler.getWindowPositionY());
		glfwSetWindowSizeLimits(mWindowHandle, mMINIMUM_SIZE_X, mMINIMUM_SIZE_Y, mMAXIMUM_SIZE_X, mMAXIMUM_SIZE_Y);
		
		if (mWindowHandle == nullptr)
		{
			throw std::wstring(L"[Window] Window could not be created.");
		}
		else
		{
			glfwMakeContextCurrent(mWindowHandle);
			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK)
			{
				throw std::wstring(L"[Window] GLEW could not be initialized.");
			}

			GLint windowWidth, windowHeight;
			glfwGetFramebufferSize(mWindowHandle, &windowWidth, &windowHeight);
			glfwSwapInterval(gameSettingsHandler.isVsyncEnabled());
			glViewport(0, 0, windowWidth, windowHeight);
		}

		mCallbackManager = new CallbackManager(this, gameSettingsHandler);
		glfwShowWindow(mWindowHandle);
	}


	GLFWwindow* Window::getWindowHandle() const
	{
		return mWindowHandle;
	}


	glm::vec2 Window::getMinimumWindowPosition() const
	{
		return glm::vec2(0, 0);
	}


	glm::vec2 Window::getMaximumWindowPosition() const
	{
		return glm::vec2(mVIDEO_MODE->width, mVIDEO_MODE->height);
	}
}