#pragma once
#ifndef BOUNTIVE_GUIENTITIES_H_
#define BOUNTIVE_GUIENTITIES_H_

#include <vector>

namespace Bountive
{
	class ResourceTracker;
	class EntityRegistry;
	class EntityGui;

	class GuiEntities
	{
	public:
		static EntityGui* mBountiveLogo;

		static void initGuis(const ResourceTracker& RESOURCE_TRACKER, EntityRegistry& entityRegistry);

	private:
		static void registerGuis(EntityRegistry& entityRegistry);

		GuiEntities();
	};
}

#endif