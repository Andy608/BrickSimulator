#pragma once
#ifndef BOUNTIVE_SCENEMANAGER_H_
#define BOUNTIVE_SCENEMANAGER_H_

#include <vector>
#include "Scene.h"

namespace Bountive
{
	class Window;
	class Logger;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void update(const Window& window, const GLdouble& DELTA_TIME);
		void render(const GLdouble& DELTA_TIME);

		Scene* getSceneById(const GLint& SCENE_ID);
		Scene* getSceneByName(const std::string& SCENE_NAME);
		Scene* getActiveScene();
		void setActiveScene(Scene* nextScene);

	private:
		static Logger logger;
		static GLint sceneIdCounter;

		std::vector<Scene*>* mGameScenes;
		Scene* mActiveScene;
		Scene* mLastScene;

		std::vector<Scene*>* createScenes();
		void clearScenesList();
	};
}

#endif