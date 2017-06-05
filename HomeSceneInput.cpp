#include "HomeSceneInput.h"
#include "InputTracker.h"
#include "BrickSimulator.h"
#include "Logger.h"

namespace Bountive
{
	Logger HomeSceneInput::logger = Logger("HomeSceneInput", Logger::Level::LEVEL_ALL);

	HomeSceneInput::HomeSceneInput() :
		SceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating HomeSceneInput...");
	}


	HomeSceneInput::~HomeSceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting HomeSceneInput...");
	}


	void HomeSceneInput::update(const GLdouble& DELTA_TIME)
	{
		if (BrickSimulator::instance->getInputTracker()->getPauseKey().isPressed() && BrickSimulator::instance->getInputTracker()->getPauseKey().isNewPress())
		{
			glfwSetWindowShouldClose(BrickSimulator::instance->getWindow()->getWindowHandle(), GL_TRUE);
		}
	}
}