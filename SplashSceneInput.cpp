#include "SplashSceneInput.h"
#include "InputTracker.h"
#include "Window.h"
#include "SceneHome.h"
#include "BooleanSetting.h"
#include "Logger.h"

namespace Bountive
{
	Logger SplashSceneInput::logger = Logger("SplashSceneInput", Logger::Level::LEVEL_ALL);

	SplashSceneInput::SplashSceneInput(const InputTracker& INPUT_TRACKER) :
		SceneInput(INPUT_TRACKER)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashSceneInput...");
	}


	SplashSceneInput::~SplashSceneInput()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashSceneInput...");
	}


	void SplashSceneInput::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		if (mINPUT_TRACKER.getEscapeKey().isPressed() && mINPUT_TRACKER.getEscapeKey().isNewPress())
		{
			window.getSceneManager().setActiveScene(HomeScene::NAME);
		}
	}
}