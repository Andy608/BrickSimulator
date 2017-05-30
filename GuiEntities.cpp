#include "GuiEntities.h"
#include "BrickSimulator.h"
#include "ResourceImage.h"
#include "MeshGui.h"
#include "EntityGui.h"
#include "EntityRegistry.h"
#include "ResourceTracker.h"

namespace Bountive
{
	EntityGui* GuiEntities::mBountiveLogo = nullptr;

	void GuiEntities::initGuis(const ResourceTracker& RESOURCE_TRACKER, EntityRegistry& entityRegistry)
	{
		//StartupResourceLoader* startupResourceLoader = RESOURCE_TRACKER.getStartupResourceLoader();

		//Make it so that not all guis need textures
		//mBountiveLogo = new EntityGui("gui_bountiveLogo", static_cast<MeshGui&>(*startupResourceLoader->mGuiMesh), new TextureWrapper(static_cast<ResourceImage*>(startupResourceLoader->findResource("image_bountiveLogo"))));

		registerGuis(entityRegistry);
	}


	void GuiEntities::registerGuis(EntityRegistry& entityRegistry)
	{
		entityRegistry.registerEntity(mBountiveLogo);
	}
}