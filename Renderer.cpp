#include "Renderer.h"
#include "ResourceTracker.h"
#include "Logger.h"

namespace Bountive
{
	Logger Renderer::logger = Logger("Renderer", Logger::Level::LEVEL_ALL);

	Renderer::Renderer(const ResourceTracker& RESOURCE_TRACKER, const SceneManager& SCENE_MANAGER) :
		mRESOURCE_TRACKER(RESOURCE_TRACKER),
		mSCENE_MANAGER(SCENE_MANAGER),
		mEntitiesList(new std::vector<Entity*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating Renderer...");
	}


	Renderer::~Renderer()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting Renderer...");
		clearEntities();
		delete mEntitiesList;
	}


	void Renderer::clearEntities()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Clearing Entities! Entities in list: " + std::to_string(mEntitiesList->size()));

		//for (GLuint i = 0; i < mEntitiesList->size(); ++i)
		//{
		//	if (mEntitiesList->at(i) != nullptr)
		//	{
		//		delete mEntitiesList->at(i);
		//	}
		//}

		mEntitiesList->clear();
	}
}