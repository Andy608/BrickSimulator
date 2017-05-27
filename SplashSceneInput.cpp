#include "SplashSceneInput.h"
#include "InputTracker.h"
#include "BrickSimulator.h"
#include "SceneHome.h"
#include "BooleanSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger SplashSceneInput::logger = Logger("SplashSceneInput", Logger::Level::LEVEL_ALL);

	SplashSceneInput::SplashSceneInput() :
		SceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashSceneInput...");
	}


	SplashSceneInput::~SplashSceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashSceneInput...");
	}


	void SplashSceneInput::update(const GLdouble& DELTA_TIME)
	{
		if (BrickSimulator::instance->getInputTracker()->getEscapeKey().isPressed() && BrickSimulator::instance->getInputTracker()->getEscapeKey().isNewPress())
		{
			BrickSimulator::instance->getSceneManager()->setActiveScene(HomeScene::NAME);
		}
	}
}