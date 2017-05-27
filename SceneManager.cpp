#include "SceneManager.h"
#include "SceneHome.h"
#include "SceneSplash.h"
#include "Logger.h"

namespace Bountive
{
	Logger SceneManager::logger = Logger("SceneManager", Logger::Level::LEVEL_ALL);
	GLint SceneManager::sceneIdCounter = -1;

	SceneManager::SceneManager() :
		mSceneList(createScenes()),
		mLastScene(findSceneByName(HomeScene::NAME)),
		mActiveScene(findSceneByName(HomeScene::NAME))
	{
		setActiveScene(SplashScene::NAME);
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


	const Scene& SceneManager::getSceneById(const GLint& sceneId) const
	{
		for (GLuint i = 0; i < mSceneList->size(); ++i)
		{
			if (mSceneList->at(i)->mID == sceneId)
			{
				return *mSceneList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find scene. Returning the current active scene.");
		return *mActiveScene;
	}


	const Scene& SceneManager::getSceneByName(const std::string& sceneName) const
	{
		return *findSceneByName(sceneName);
	}


	Scene* SceneManager::findSceneByName(const std::string& sceneName) const
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


	const Scene& SceneManager::getActiveScene() const
	{
		return *mActiveScene;
	}


	void SceneManager::setActiveScene(const std::string& NEXT_SCENE_NAME)
	{
		mLastScene = mActiveScene;
		mActiveScene = findSceneByName(NEXT_SCENE_NAME);

		mLastScene->hideScene();
		mActiveScene->showScene();

		logger.log(Logger::Level::LEVEL_DEBUG, "Switching Scene!");
	}


	std::vector<Scene*>* SceneManager::createScenes()
	{
		std::vector<Scene*>* gameScenes = new std::vector<Scene*>();

		gameScenes->push_back(new HomeScene(++sceneIdCounter));
		gameScenes->push_back(new SplashScene(++sceneIdCounter));

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