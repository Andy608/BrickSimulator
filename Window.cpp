#include <glm\vec2.hpp>
#include <string>
#include "BrickSimulator.h"
#include "CallbackManager.h"
#include "FileSettingsHandler.h"
#include "WindowSizeCallback.h"
#include "GraphicsOptions.h"
#include "InputTracker.h"
#include "Logger.h"

namespace Bountive
{
	Logger Window::logger = Logger("Window", Logger::Level::LEVEL_ALL);
	GLint Window::DECORATION_HEIGHT = 23;

	const GLFWvidmode* Window::initGLFW()
	{
		if (!glfwInit())
		{
			std::wstring error = L"GLFW init failed.";
			logger.log(Logger::Level::LEVEL_FATAL, error);
			throw(error);
		}
		else
		{
			return glfwGetVideoMode(glfwGetPrimaryMonitor());
		}
	}

	Window::Window() :
		mVIDEO_MODE(initGLFW()),
		mMINIMUM_SIZE_X(static_cast<GLint>(mVIDEO_MODE->width / 16.0f)),
		mMINIMUM_SIZE_Y(1),
		mMAXIMUM_SIZE_X(mVIDEO_MODE->width),
		mMAXIMUM_SIZE_Y(mVIDEO_MODE->height - DECORATION_HEIGHT)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating Window...");
	}


	Window::~Window()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting Window...");
		delete mCallbackManager;
		glfwTerminate();
	}


	void Window::buildWindow(FileSettingsHandler& fileSettingsHandler)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		if (fileSettingsHandler.isWindowMaximized().getCustomBoolean())
		{
			glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		}

		mWindowHandle = glfwCreateWindow(fileSettingsHandler.getWindowWidth().getCustomInteger(), fileSettingsHandler.getWindowHeight().getCustomInteger(), "Brick Simulator 2017", nullptr, nullptr);

		if (!fileSettingsHandler.isWindowMaximized().getCustomBoolean())
		{
			glfwSetWindowPos(mWindowHandle, fileSettingsHandler.getWindowPositionX().getCustomInteger(), fileSettingsHandler.getWindowPositionY().getCustomInteger());
		}

		glfwSetWindowSizeLimits(mWindowHandle, mMINIMUM_SIZE_X, mMINIMUM_SIZE_Y, mMAXIMUM_SIZE_X, mMAXIMUM_SIZE_Y);
		glfwHideWindow(mWindowHandle);
		
		if (mWindowHandle == nullptr)
		{
			std::wstring error = L"Window could not be created.";
			logger.log(Logger::Level::LEVEL_FATAL, error);
			glfwTerminate();
			throw std::wstring(error);
		}
		else
		{
			glfwMakeContextCurrent(mWindowHandle);
			glewExperimental = GL_TRUE;

			if (glewInit() != GLEW_OK)
			{
				std::wstring error = L"GLEW could not be initialized.";
				logger.log(Logger::Level::LEVEL_FATAL, error);
				glfwTerminate();
				throw std::wstring(error);
			}

			GLint windowWidth, windowHeight;
			glfwGetFramebufferSize(mWindowHandle, &windowWidth, &windowHeight);
			glfwSwapInterval(GraphicsOptions::instance->isVsyncEnabled().getCustomBoolean());
			glViewport(0, 0, windowWidth, windowHeight);

			mCallbackManager = new CallbackManager(fileSettingsHandler);

			glfwShowWindow(mWindowHandle);
		}
	}


	void Window::update(const GLdouble& DELTA_TIME)
	{
		
	}


	void Window::render(const GLdouble& DELTA_TIME)
	{

	}


	GLFWwindow* Window::getWindowHandle() const
	{
		return mWindowHandle;
	}


	glm::vec2 Window::getMinimumWindowPosition() const
	{
		return glm::vec2(0, DECORATION_HEIGHT);
	}


	glm::vec2 Window::getMaximumWindowPosition() const
	{
		return glm::vec2(mVIDEO_MODE->width, mVIDEO_MODE->height);
	}
}