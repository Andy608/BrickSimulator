#pragma once
#ifndef BOUNTIVE_SCENEMANAGER_H_
#define BOUNTIVE_SCENEMANAGER_H_

#include <vector>
#include "Scene.h"
#include "ResourceBundleTracker.h"

namespace Bountive
{
	class RenderManager;
	class Logger;

	class SceneManager
	{
	public:
		SceneManager(ResourceBundleTracker& resourceBundleTracker, RenderManager& renderManager);
		~SceneManager();

		void update(const GLdouble& DELTA_TIME);
		void render(const GLdouble& DELTA_TIME);

		const Scene& getSceneById(const GLint& SCENE_ID) const;
		const Scene& getSceneByName(const std::string& SCENE_NAME) const;
		const Scene& getActiveScene() const;
		void setActiveScene(const std::string& NEXT_SCENE_NAME);

	private:
		static Logger logger;
		static GLint sceneIdCounter;

		ResourceBundleTracker& mResourceBundleTracker;
		RenderManager& mRenderManager;

		std::vector<Scene*>* mSceneList;
		Scene* mActiveScene;
		Scene* mLastScene;

		std::vector<Scene*>* createScenes();
		Scene* findSceneByName(const std::string& SCENE_NAME) const;
		void clearScenesList();
	};
}

#endif