#pragma once
#ifndef BOUNTIVE_GUIENTITIES_H_
#define BOUNTIVE_GUIENTITIES_H_

#include <vector>

namespace Bountive
{
	class AssetManager;
	class EntityRegistry;
	class EntityGui;

	class GuiEntities
	{
	public:
		static EntityGui* mBountiveLogo;

		static void initGuis(const AssetManager& ASSET_MANAGER, EntityRegistry& entityRegistry);

	private:
		static void registerGuis(EntityRegistry& entityRegistry);

		GuiEntities();
	};
}

#endif