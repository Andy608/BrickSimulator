#include "EntityTracker.h"
#include "Logger.h"

namespace Bountive
{
	Logger EntityTracker::logger = Logger("EntityTracker", Logger::Level::LEVEL_ALL);

	EntityTracker::EntityTracker() :
		mActiveEntityList(new std::vector<Entity*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating EntityTracker...");
	}


	EntityTracker::~EntityTracker()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting EntityTracker...");

		for (GLuint i = 0; i < mActiveEntityList->size(); ++i)
		{
			if (mActiveEntityList->at(i) != nullptr)
			{
				delete mActiveEntityList->at(i);
			}
		}

		mActiveEntityList->clear();
		delete mActiveEntityList;
	}


	void EntityTracker::addEntity(Entity* entity)
	{
		for (GLuint i = 0; i < mActiveEntityList->size(); ++i)
		{
			if (mActiveEntityList->at(i) == entity)
			{
				logger.log(Logger::Level::LEVEL_DEBUG, "Entity is already in the list.");
				return;
			}
		}

		mActiveEntityList->push_back(entity);
	}


	void EntityTracker::removeEntity(Entity* entity)
	{
		for (GLuint i = 0; i < mActiveEntityList->size(); ++i)
		{
			if (mActiveEntityList->at(i) == entity)
			{
				mActiveEntityList->erase(mActiveEntityList->begin() + i);
				logger.log(Logger::Level::LEVEL_DEBUG, "Erased entity at index: " + std::to_string(i));
				return;
			}
		}

		logger.log(Logger::Level::LEVEL_DEBUG, "Could not find entity in list.");
	}
}