#pragma once
#ifndef BOUNTIVE_RENDERER_H_
#define BOUNTIVE_RENDERER_H_

#include <vector>
#include "Entity.h"
#include "IUpdatable.h"
#include "IRenderable.h"

namespace Bountive
{
	class ResourceTracker;
	class SceneManager;
	class Logger;

	class Renderer : public IUpdatable, public IRenderable
	{
	public:
		Renderer(const ResourceTracker& ASSET_MANAGER, const SceneManager& SCENE_MANAGER);
		virtual ~Renderer();

		void clearEntities();

	protected:
		std::vector<Entity*>* mEntitiesList;

	protected:
		const ResourceTracker& mRESOURCE_TRACKER;
		const SceneManager& mSCENE_MANAGER;

	private:
		static Logger logger;
	};
}

#endif