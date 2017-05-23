#include "SceneManager.h"
#include "SceneHome.h"
#include "SceneSplash.h"
#include "Window.h"
#include "Logger.h"

namespace Bountive
{
	Logger SceneManager::logger = Logger("SceneManager", Logger::Level::LEVEL_ALL);
	GLint SceneManager::sceneIdCounter = -1;

	SceneManager::SceneManager(const Window& WINDOW_HANDLE) :
		mSceneList(createScenes(WINDOW_HANDLE)),
		mActiveScene(getSceneByName(SplashScene::NAME)),
		mLastScene(getSceneByName(HomeScene::NAME))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SceneManager...");
	}


	SceneManager::~SceneManager()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SceneManager...");
		clearScenesList();
		delete mSceneList;
	}


	void SceneManager::update(const GLdouble& DELTA_TIME)
	{
		mActiveScene->update(DELTA_TIME);
	}


	void SceneManager::render(const GLdouble& DELTA_TIME)
	{
		mActiveScene->render(DELTA_TIME);
	}


	Scene* SceneManager::getSceneById(const GLint& sceneId)
	{
		for (GLuint i = 0; i < mSceneList->size(); ++i)
		{
			if (mSceneList->at(i)->mID == sceneId)
			{
				return mSceneList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find scene. Returning the current active scene.");
		return mActiveScene;
	}


	Scene* SceneManager::getSceneByName(const std::string& sceneName)
	{
		for (GLuint i = 0; i < mSceneList->size(); ++i)
		{
			if (mSceneList->at(i)->getName().compare(sceneName) == 0)
			{
				return mSceneList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find scene. Returning the current active scene.");
		return mActiveScene;
	}


	Scene* SceneManager::getActiveScene()
	{
		return mActiveScene;
	}


	void SceneManager::setActiveScene(const std::string& NEXT_SCENE_NAME)
	{
		mLastScene = mActiveScene;
		mActiveScene = getSceneByName(NEXT_SCENE_NAME);
		logger.log(Logger::Level::LEVEL_DEBUG, "Switching Scene!");
	}


	std::vector<Scene*>* SceneManager::createScenes(const Window& WINDOW_HANDLE)
	{
		std::vector<Scene*>* gameScenes = new std::vector<Scene*>();

		gameScenes->push_back(new HomeScene(WINDOW_HANDLE, ++sceneIdCounter));
		gameScenes->push_back(new SplashScene(WINDOW_HANDLE, ++sceneIdCounter));

		return gameScenes;
	}


	void SceneManager::clearScenesList()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Clearing Scenes! Scenes in list: " + std::to_string(mSceneList->size()));

		for (GLuint i = 0; i < mSceneList->size(); ++i)
		{
			if (mSceneList->at(i) != nullptr)
			{
				delete mSceneList->at(i);
			}
		}

		mSceneList->clear();
	}
}