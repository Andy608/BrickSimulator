#include "HomeSceneInput.h"
#include "InputTracker.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger HomeSceneInput::logger = Logger("HomeSceneInput", Logger::Level::LEVEL_ALL);

	HomeSceneInput::HomeSceneInput(const InputTracker& INPUT_TRACKER) :
		SceneInput(INPUT_TRACKER)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating HomeSceneInput...");
	}


	HomeSceneInput::~HomeSceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting HomeSceneInput...");
	}


	void HomeSceneInput::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		if (mINPUT_TRACKER.getEscapeKey().isPressed() && mINPUT_TRACKER.getEscapeKey().isNewPress())
		{
			glfwSetWindowShouldClose(window.getWindowHandle(), GL_TRUE);
		}
	}
}