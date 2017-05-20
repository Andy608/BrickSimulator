#include "HomeSceneInput.h"
#include "InputTracker.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger HomeSceneInput::logger = Logger("HomeSceneInput", Logger::Level::LEVEL_ALL);

	HomeSceneInput::HomeSceneInput(const InputTracker& INPUT_TRACKER) :
		mINPUT_TRACKER(INPUT_TRACKER)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating HomeSceneInput...");
	}


	HomeSceneInput::~HomeSceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting HomeSceneInput...");
	}


	void HomeSceneInput::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		//Depending on screen do something else.

		if (mINPUT_TRACKER.isKeyEscapePressed())
		{
			glfwSetWindowShouldClose(window.getWindowHandle(), GL_TRUE);
		}
	}
}