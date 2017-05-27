#include "Renderer.h"
#include "AssetManager.h"
#include "Logger.h"

namespace Bountive
{
	Logger Renderer::logger = Logger("Renderer", Logger::Level::LEVEL_ALL);

	Renderer::Renderer(const AssetManager& ASSET_MANAGER, const SceneManager& SCENE_MANAGER) :
		mASSET_MANAGER(ASSET_MANAGER),
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