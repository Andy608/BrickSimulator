#include "GuiEntities.h"
#include "BrickSimulator.h"
#include "AssetImage.h"
#include "AssetMeshGui.h"
#include "EntityGui.h"
#include "EntityRegistry.h"
#include "AssetManager.h"

namespace Bountive
{
	EntityGui* GuiEntities::mBountiveLogo = nullptr;

	void GuiEntities::initGuis(const AssetManager& ASSET_MANAGER, EntityRegistry& entityRegistry)
	{
		PregameAssetLoader* pregameAssetLoader = ASSET_MANAGER.getPregameAssetLoader();

		//Make it so that not all guis need textures
		mBountiveLogo = new EntityGui(L"gui_bountiveLogo", static_cast<AssetMeshGui&>(*pregameAssetLoader->mGuiMesh), new TextureWrapper(static_cast<AssetImage*>(pregameAssetLoader->findAsset(L"image_bountiveLogo"))));

		registerGuis(entityRegistry);
	}


	void GuiEntities::registerGuis(EntityRegistry& entityRegistry)
	{
		entityRegistry.registerEntity(mBountiveLogo);
	}
}