#pragma once
#ifndef BOUNTIVE_RENDERMANAGER_H_
#define BOUNTIVE_RENDERMANAGER_H_

#include "ResourceTracker.h"
#include "GuiRenderer.h"

namespace Bountive
{
	class SceneManager;

	class RenderManager
	{
	public:
		RenderManager(const SceneManager& SCENE_MANAGER);
		~RenderManager();

		ResourceTracker* getResourceTracker() const;
		GuiRenderer* getGuiRenderer() const;

	private:
		const SceneManager& mSCENE_MANAGER;
		ResourceTracker* mResourceTracker;
		GuiRenderer* mGuiRenderer;
	};
}

#endif