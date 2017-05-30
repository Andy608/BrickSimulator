#include "RenderManager.h"
#include "Window.h"
#include "SceneHome.h"

namespace Bountive
{
	RenderManager::RenderManager(const SceneManager& SCENE_MANAGER) :
		mSCENE_MANAGER(SCENE_MANAGER),
		mResourceTracker(new ResourceTracker()),
		mGuiRenderer(new GuiRenderer(*mResourceTracker, mSCENE_MANAGER))
	{
		mResourceTracker->initResourcePackage(ResourceLoader::ResourcePackageId::START_UP);
		mResourceTracker->loadResourcePackage(ResourceLoader::ResourcePackageId::START_UP);
	}


	RenderManager::~RenderManager()
	{
		delete mGuiRenderer;
		delete mResourceTracker;
	}


	ResourceTracker* RenderManager::getResourceTracker() const
	{
		return mResourceTracker;
	}


	GuiRenderer* RenderManager::getGuiRenderer() const
	{
		return mGuiRenderer;
	}
}