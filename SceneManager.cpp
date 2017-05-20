#include "SceneManager.h"
#include "HomeScene.h"
#include "Logger.h"

namespace Bountive
{
	Logger SceneManager::logger = Logger("SceneManager", Logger::Level::LEVEL_ALL);
	GLint SceneManager::sceneIdCounter = -1;

	SceneManager::SceneManager() :
		mGameScenes(createScenes()),
		mActiveScene(getSceneByName(HomeScene::NAME)),
		mLastScene(getSceneByName(HomeScene::NAME))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating SceneManager...");
	}


	SceneManager::~SceneManager()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting SceneManager...");
		clearScenesList();
		delete mGameScenes;
	}


	void SceneManager::update(const Window& window, const GLdouble& DELTA_TIME)
	{
		mActiveScene->update(window, DELTA_TIME);
	}


	void SceneManager::render(const GLdouble& DELTA_TIME)
	{
		mActiveScene->render(DELTA_TIME);
	}


	Scene* SceneManager::getSceneById(const GLint& sceneId)
	{
		for (GLuint i = 0; i < mGameScenes->size(); ++i)
		{
			if (mGameScenes->at(i)->mID == sceneId)
			{
				return mGameScenes->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find scene. Returning the current active scene.");
		return mActiveScene;
	}


	Scene* SceneManager::getSceneByName(const std::string& sceneName)
	{
		for (GLuint i = 0; i < mGameScenes->size(); ++i)
		{
			if (mGameScenes->at(i)->getName().compare(sceneName) == 0)
			{
				return mGameScenes->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find scene. Returning the current active scene.");
		return mActiveScene;
	}


	Scene* SceneManager::getActiveScene()
	{
		return mActiveScene;
	}


	void SceneManager::setActiveScene(Scene* nextScene)
	{
		mLastScene = mActiveScene;
		mActiveScene = nextScene;
	}


	std::vector<Scene*>* SceneManager::createScenes()
	{
		std::vector<Scene*>* gameScenes = new std::vector<Scene*>();

		gameScenes->push_back(new HomeScene(++sceneIdCounter));
		
		return gameScenes;
	}


	void SceneManager::clearScenesList()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Clearing Scenes! Scenes in list: " + std::to_string(mGameScenes->size()));

		for (GLuint i = 0; i < mGameScenes->size(); ++i)
		{
			if (mGameScenes->at(i) != nullptr)
			{
				delete mGameScenes->at(i);
			}
		}

		mGameScenes->clear();
	}
}