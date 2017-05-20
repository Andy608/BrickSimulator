#include "SceneSplash.h"
#include "SplashSceneInput.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger SplashScene::logger = Logger("SplashScene", Logger::Level::LEVEL_ALL);
	const std::string SplashScene::NAME = "splash_scene";

	SplashScene::SplashScene(Window* window, GLint id) :
		Scene(id, NAME),
		mInputHandler(new SplashSceneInput(window->getInputTracker()))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashScene...");
	}


	SplashScene::~SplashScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashScene...");
		delete mInputHandler;
	}


	void SplashScene::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		mInputHandler->update(window, DELTA_TIME);
	}


	void SplashScene::render(const GLdouble& DELTA_TIME)
	{
		glClearColor(0.8f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}