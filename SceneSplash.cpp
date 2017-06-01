#include "SceneSplash.h"
#include "SplashSceneInput.h"
#include "KeyboardCallback.h"
#include "MeshList.h"
#include "GuiResourceBundle.h"
#include <glm\glm.hpp>
#include "Logger.h"

namespace Bountive
{
	Logger SplashScene::logger = Logger("SplashScene", Logger::Level::LEVEL_ALL);
	const std::string SplashScene::NAME = "splash_scene";

	SplashScene::SplashScene(GLint id, RenderManager& renderManager) :
		Scene(id, NAME, renderManager),
		mInputHandler(new SplashSceneInput())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashScene...");
	}


	SplashScene::~SplashScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashScene...");
		delete mInputHandler;
	}


	void SplashScene::showScene()
	{
		TextureWrapper* bountiveTexture = new TextureWrapper(GuiResourceBundle::mBountiveLogoTexture);
		bountiveTexture->setMinifyFilter(TextureWrapper::MinFilter::LINEAR_MIPMAP_LINEAR);
		bountiveTexture->setMaxifyFilter(TextureWrapper::MaxFilter::LINEAR);

		bountiveLogo = new EntityGui("gui_bountive_logo", bountiveTexture);
		bountiveLogo->getTransform()->setScale(0.5f, 0.5f, 1.0f);

		logger.log(Logger::Level::LEVEL_DEBUG, "SHOWING SPLASH SCENE... " + std::to_string(mGuiList->size()));

		mGuiList->push_back(bountiveLogo);
	}


	void SplashScene::hideScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "HIDING SPLASH SCENE... " + std::to_string(mGuiList->size()));
		clearGuiList();
	}


	void SplashScene::update(const GLdouble& DELTA_TIME)
	{
		static GLfloat t = 0;
		t += DELTA_TIME;
		bountiveLogo->getTransform()->setPosition(0.5f * std::sin(glm::radians(50 * t)), 0, 0);

		mInputHandler->update(DELTA_TIME);
	}


	void SplashScene::render(const GLdouble& DELTA_TIME)
	{
		logger.log(Logger::Level::LEVEL_TRACE, "SPLASH");

		glClearColor(1.0f, 208.0f / 255.0f, 82.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene::render(DELTA_TIME);
	}
}