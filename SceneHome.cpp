#include "BrickSimulator.h"
#include "SceneHome.h"
#include "HomeSceneInput.h"
#include "KeyboardCallback.h"
#include "Logger.h"

namespace Bountive
{
	Logger HomeScene::logger = Logger("HomeScene", Logger::Level::LEVEL_ALL);
	const std::string HomeScene::NAME = "home_scene";

	HomeScene::HomeScene(GLint id, RenderManager& renderManager) :
		Scene(id, NAME, renderManager),
		mInputHandler(new HomeSceneInput())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating HomeScene...");
	}


	HomeScene::~HomeScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting HomeScene...");
		delete mInputHandler;
	}


	void HomeScene::showScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "SHOWING HOME SCENE... " + std::to_string(mGuiList->size()));
	}

	void HomeScene::hideScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "HIDING HOME SCENE... " + std::to_string(mGuiList->size()));
	}


	void HomeScene::update(const GLdouble& DELTA_TIME)
	{
		mInputHandler->update(DELTA_TIME);
	}


	void HomeScene::render(const GLdouble& DELTA_TIME)
	{
		logger.log(Logger::Level::LEVEL_TRACE, "HOME");

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene::render(DELTA_TIME);
	}
}