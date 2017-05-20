#include "SceneHome.h"
#include "HomeSceneInput.h"
#include "KeyboardCallback.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger HomeScene::logger = Logger("HomeScene", Logger::Level::LEVEL_ALL);
	const std::string HomeScene::NAME = "home_scene";

	HomeScene::HomeScene(Window* window, GLint id) :
		Scene(id, NAME),
		mInputHandler(new HomeSceneInput(window->getInputTracker()))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating HomeScene...");
	}


	HomeScene::~HomeScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting HomeScene...");
		delete mInputHandler;
	}


	void HomeScene::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		mInputHandler->update(window, DELTA_TIME);
	}


	void HomeScene::render(const GLdouble& DELTA_TIME)
	{
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}