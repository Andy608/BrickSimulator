#include "FramebufferSizeCallback.h"
#include "RenderManager.h"
#include "Logger.h"

namespace Bountive
{
	FramebufferSizeCallback* FramebufferSizeCallback::instance = nullptr;
	Logger FramebufferSizeCallback::logger = Logger("FramebufferSizeCallback", Logger::Level::LEVEL_ALL);

	FramebufferSizeCallback* FramebufferSizeCallback::init()
	{
		if (instance == nullptr)
		{
			instance = new FramebufferSizeCallback();
		}

		return instance;
	}


	FramebufferSizeCallback::FramebufferSizeCallback() 
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating FramebufferSizeCallback...");
	}


	FramebufferSizeCallback::~FramebufferSizeCallback()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting FramebufferSizeCallback...");
	}


	void FramebufferSizeCallback::framebufferSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
	{
		//logger.log(Logger::Level::LEVEL_TRACE, "Framebuffer Width: " + std::to_string(windowWidth)+ " | Framebuffer Height: " + std::to_string(windowHeight));
		glViewport(0, 0, windowWidth, windowHeight);
		RenderManager::updateRenderScreenSize(windowWidth, windowHeight);
	}
}