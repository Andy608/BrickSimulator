#include "SceneSplash.h"
#include "SplashSceneInput.h"
#include "KeyboardCallback.h"
#include "GuiEntities.h"
#include "Logger.h"

namespace Bountive
{
	Logger SplashScene::logger = Logger("SplashScene", Logger::Level::LEVEL_ALL);
	const std::string SplashScene::NAME = "splash_scene";

	SplashScene::SplashScene(GLint id) :
		Scene(id, NAME),
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
		//add gui adds an entity (with position/rot/scale)
		//mRenderManager.getAssetManager()->getPregameAssetLoader()->mGuiShaderProgram->use();
		//mRenderManager.getGuiRenderer()->addGui(GuiEntities::mBountiveLogo);
	}


	void SplashScene::hideScene()
	{
		mRenderManager.getGuiRenderer()->clearEntities();
	}


	void SplashScene::update(const GLdouble& DELTA_TIME)
	{
		mInputHandler->update(DELTA_TIME);
		mRenderManager.getGuiRenderer()->update(DELTA_TIME);
	}


	void SplashScene::render(const GLdouble& DELTA_TIME)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//mRenderManager.getResourceTracker()->getStartupResourceLoader()->mGuiShaderProgram->use();

		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, GuiEntities::mBountiveLogo->getTextureWrapper().getId());
		//glUniform1i(glGetUniformLocation(mRenderManager.getResourceTracker()->getStartupResourceLoader()->mGuiShaderProgram->getProgramId(), "bountiveLogo"), 0);

		mRenderManager.getGuiRenderer()->render(DELTA_TIME);
	}
}