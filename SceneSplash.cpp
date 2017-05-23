#include "SceneSplash.h"
#include "SplashSceneInput.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger SplashScene::logger = Logger("SplashScene", Logger::Level::LEVEL_ALL);
	const std::string SplashScene::NAME = "splash_scene";

	SplashScene::SplashScene(const Window& WINDOW_HANDLE, GLint id) :
		Scene(WINDOW_HANDLE, id, NAME),
		mInputHandler(new SplashSceneInput(WINDOW_HANDLE.getInputTracker()))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashScene...");
	}


	SplashScene::~SplashScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashScene...");
		delete mInputHandler;
	}


	void SplashScene::update(const GLdouble& DELTA_TIME)
	{
		mInputHandler->update(mWINDOW_HANDLE, DELTA_TIME);
	}


	void SplashScene::render(const GLdouble& DELTA_TIME)
	{
		glClearColor(0.8f, 0.6f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}