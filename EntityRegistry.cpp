#include "EntityRegistry.h"
#include "Logger.h"

namespace Bountive
{
	Logger EntityRegistry::logger = Logger("EntityRegistry", Logger::Level::LEVEL_ALL);

	EntityRegistry::EntityRegistry() :
		mEntityList(new std::vector<Entity*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating EntityRegistry...");
	}


	EntityRegistry::~EntityRegistry()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting EntityRegistry...");
		clearEntityRegistry();
		delete mEntityList;
	}


	void EntityRegistry::registerEntity(Entity* entity)
	{
		for (GLuint i = 0; i < mEntityList->size(); ++i)
		{
			if (mEntityList->at(i)->getEntityId().compare(entity->getEntityId()) == 0)
			{
				std::wstring entityRegistryError = L"Cannot register entity with id: " + entity->getEntityId() + L". Entity with id is already in use.";
				logger.log(Logger::Level::LEVEL_WARN, entityRegistryError);
				throw(entityRegistryError);
			}
		}
		mEntityList->push_back(entity);
	}


	Entity* EntityRegistry::getEntityFromRegistry(std::wstring entityId)
	{
		for (GLuint i = 0; i < mEntityList->size(); ++i)
		{
			if (mEntityList->at(i)->getEntityId().compare(entityId) == 0)
			{
				return mEntityList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, L"Could not find entity with id: " + entityId + L" in the registry list.");
		return nullptr;
	}


	void EntityRegistry::clearEntityRegistry()
	{
		logger.log(Logger::Level::LEVEL_WARN, L"Entities in EntityRegistry: " + std::to_wstring(mEntityList->size()));

		for (GLuint i = 0; i < mEntityList->size(); ++i)
		{
			if (mEntityList->at(i) != nullptr)
			{
				delete mEntityList->at(i);
			}
		}

		mEntityList->clear();
	}
}