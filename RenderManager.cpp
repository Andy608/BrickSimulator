#include "RenderManager.h"
#include "Window.h"
#include "SceneHome.h"

namespace Bountive
{
	RenderManager::RenderManager(const SceneManager& SCENE_MANAGER) :
		mSCENE_MANAGER(SCENE_MANAGER),
		mAssetManager(new AssetManager()),
		mGuiRenderer(new GuiRenderer(*mAssetManager, mSCENE_MANAGER))
	{

	}


	RenderManager::~RenderManager()
	{
		delete mGuiRenderer;
		delete mAssetManager;
	}


	AssetManager* RenderManager::getAssetManager() const
	{
		return mAssetManager;
	}


	GuiRenderer* RenderManager::getGuiRenderer() const
	{
		return mGuiRenderer;
	}
}