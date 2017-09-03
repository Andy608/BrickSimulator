#include "SceneSplash.h"
#include "SplashSceneInput.h"
#include "KeyboardCallback.h"
#include "MeshList.h"
#include "ModelResourceBundle.h"
#include "GuiResourceBundle.h"
#include "WindowSizeCallback.h"
#include <glm\glm.hpp>
#include "Logger.h"

namespace Bountive
{
	Logger SplashScene::logger = Logger("SplashScene", Logger::Level::LEVEL_ALL);
	const std::string SplashScene::NAME = "splash_scene";

	SplashScene::SplashScene(GLint id, Window& window, RenderManager& renderManager) :
		Scene(id, NAME, window, renderManager),
		mInputHandler(new SplashSceneInput()),
		mCamera(new FreeRoamCamera(glm::vec3(0, 0, 0), 1.0f))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SplashScene...");
	}


	SplashScene::~SplashScene()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SplashScene...");
		delete mInputHandler;
		delete mCamera;
	}


	void SplashScene::showScene()
	{
		glfwSetInputMode(mWindow.getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//TextureWrapper* bountiveTexture = new TextureWrapper(GuiResourceBundle::mBountiveLogoTexture);
		//bountiveTexture->setMinifyFilter(TextureWrapper::MinFilter::LINEAR_MIPMAP_LINEAR);
		//bountiveTexture->setMaxifyFilter(TextureWrapper::MaxFilter::LINEAR);

		//bountiveLogo = new EntityGui("gui_bountive_logo", bountiveTexture);
		//bountiveLogo->getTransform()->setPosition(0.0f, 0.0f, 0.0f);

		//logger.log(Logger::Level::LEVEL_DEBUG, "SHOWING SPLASH SCENE... " + std::to_string(mGuiList->size()));

		//mGuiList->push_back(bountiveLogo);
		//InputTracker::instance->setCursorPosition(mWindow, WindowSizeCallback::instance->getWindowCenter());
		mRenderManager.setCamera(mCamera);

		mBarrel = new EntityBarrel();
		mEntityList->push_back(mBarrel);
	}


	void SplashScene::hideScene()
	{
		glfwSetInputMode(mWindow.getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//logger.log(Logger::Level::LEVEL_DEBUG, "HIDING SPLASH SCENE... " + std::to_string(mGuiList->size()));
		clearEntityList();
	}


	void SplashScene::update(const GLdouble& DELTA_TIME)
	{
		//static GLdouble t = 0;
		//t += DELTA_TIME;
		//mBarrel->getTransform()->setPosition(0.5f * static_cast<GLfloat>(std::sin(glm::radians(50.0f * t))), 0, 0);

		//InputTracker::instance->setCursorPosition(mWindow, WindowSizeCallback::instance->getWindowCenter());
		mInputHandler->update(DELTA_TIME);
	}


	void SplashScene::render(const GLdouble& DELTA_TIME)
	{
		logger.log(Logger::Level::LEVEL_TRACE, "SPLASH");

		//glClearColor(1.0f, 208.0f / 255.0f, 82.0f / 255.0f, 1.0f);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene::render(DELTA_TIME);
		mCamera->render(DELTA_TIME);
	}
}