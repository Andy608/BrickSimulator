#pragma once
#ifndef BOUNTIVE_RENDERMANAGER_H_
#define BOUNTIVE_RENDERMANAGER_H_

#include "AssetManager.h"
#include "GuiRenderer.h"

namespace Bountive
{
	class SceneManager;

	class RenderManager
	{
	public:
		RenderManager(const SceneManager& SCENE_MANAGER);
		~RenderManager();

		AssetManager* getAssetManager() const;
		GuiRenderer* getGuiRenderer() const;

	private:
		const SceneManager& mSCENE_MANAGER;
		AssetManager* mAssetManager;
		GuiRenderer* mGuiRenderer;
	};
}

#endif