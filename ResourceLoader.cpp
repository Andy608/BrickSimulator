#include "ResourceLoader.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceLoader::logger = Logger("ResourceLoader", Logger::Level::LEVEL_ALL);

	ResourceLoader::ResourceLoader(const ResourcePackageId& PACKAGE_ID) :
		mRESOURCE_PACKAGE_ID(PACKAGE_ID),
		mResourceList(new std::vector<Resource*>()),
		mPercentLoaded(0)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceLoader...");
	}


	ResourceLoader::~ResourceLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceLoader...");
		clearResourceList();
		delete mResourceList;
	}


	void ResourceLoader::addResource(Resource* asset)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Adding asset: " + asset->getResourceId());
		mResourceList->push_back(asset);
	}

	void ResourceLoader::loadResources()
	{
		//Look into using another thread for asset loader
		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			mResourceList->at(i)->load();
			mPercentLoaded = ((i + 1) / static_cast<GLfloat>(mResourceList->size())) * 100.0f;
			logger.log(Logger::Level::LEVEL_DEBUG, "Loaded asset: " + mResourceList->at(i)->getResourceId() +
				" Percent Loaded = " + std::to_string(mPercentLoaded));
		}
	}


	void ResourceLoader::unloadResources()
	{
		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			mResourceList->at(i)->unload();
			mPercentLoaded = (((mResourceList->size() - 1) - i) / mResourceList->size()) * 100.0f;
			logger.log(Logger::Level::LEVEL_DEBUG, "Unloaded asset: " + mResourceList->at(i)->getResourceId() +
				" Percent Loaded = " + std::to_string(mPercentLoaded));
		}
	}


	Resource* ResourceLoader::findResource(std::string assetId)
	{
		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			if (mResourceList->at(i)->getResourceId().compare(assetId))
			{
				return mResourceList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find asset with id: " + assetId);
		return nullptr;
	}


	void ResourceLoader::clearResourceList()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "ResourceList has " + std::to_string(mResourceList->size()) + " resources before clearing...");

		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			if (mResourceList->at(i) != nullptr)
			{
				logger.log(Logger::Level::LEVEL_DEBUG, mResourceList->at(i)->getResourceId() + " cleared and deleted!");
				delete mResourceList->at(i);
			}
		}

		mResourceList->clear();
		logger.log(Logger::Level::LEVEL_DEBUG, "ResourceList has " + std::to_string(mResourceList->size()) + " resources after clearing.");
	}
}