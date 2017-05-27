#pragma once
#ifndef BOUNTIVE_ENTITYREGISTRY_H_
#define BOUNTIVE_ENTITYREGISTRY_H_

#include <vector>
#include "Entity.h"

namespace Bountive
{
	class Logger;

	class EntityRegistry
	{
	public:
		EntityRegistry();
		~EntityRegistry();

		void registerEntity(Entity* entity);
		Entity* getEntityFromRegistry(std::wstring entityId);

	private:
		static Logger logger;

		std::vector<Entity*>* mEntityList;

		void clearEntityRegistry();
	};
}

#endif