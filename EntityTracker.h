#pragma once
#ifndef BOUNTIVE_ENTITYTRACKER_H_
#define BOUNTIVE_ENTITYTRACKER_H_

#include <vector>
#include "Entity.h"

namespace Bountive
{
	class Logger;

	class EntityTracker
	{
	public:
		EntityTracker();
		~EntityTracker();

		void addEntity(Entity* entity);
		void removeEntity(Entity* entity);

	private:
		static Logger logger;
		std::vector<Entity*>* mActiveEntityList;
	};
}

#endif