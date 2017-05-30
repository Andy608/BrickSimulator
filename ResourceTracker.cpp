#include "ResourceTracker.h"
#include "StartupResourceLoader.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceTracker::logger = Logger("ResourceTracker", Logger::Level::LEVEL_ALL);

	ResourceTracker::ResourceTracker() :
		mStartupResourceManager(new StartupResourceLoader()),
		mTotalPercentLoaded(0)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceTracker...");
	}


	ResourceTracker::~ResourceTracker()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceTracker...");
		delete mStartupResourceManager;
	}


	void ResourceTracker::initResourcePackage(const ResourceLoader::ResourcePackageId& PACKAGE_ID)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Initializing ResourceTracker...");

		switch (PACKAGE_ID)
		{
		case ResourceLoader::ResourcePackageId::START_UP:	mStartupResourceManager->initResources();
															break;
		default:
			logger.log(Logger::Level::LEVEL_WARN, "Cannot initialize resource loader. No loader with that package id.");
		}
	}


	void ResourceTracker::loadResourcePackage(const ResourceLoader::ResourcePackageId& PACKAGE_ID)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Loading ResourceTracker...");
		
		switch (PACKAGE_ID)
		{
		case ResourceLoader::ResourcePackageId::START_UP:	mStartupResourceManager->loadResources();
			break;
		default:
			logger.log(Logger::Level::LEVEL_WARN, "Cannot load resource loader. No loader with that package id.");
		}
	}
}