#include "AssetManager.h"
#include "PregameAssetLoader.h"
#include "Logger.h"

namespace Bountive
{
	Logger AssetManager::logger = Logger("AssetManager", Logger::Level::LEVEL_ALL);

	AssetManager::AssetManager() :
		mPregameAssetManager(new PregameAssetLoader()),
		mTotalPercentLoaded(0)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetManager...");
		mPregameAssetManager->initAssets();
		mPregameAssetManager->loadAssets();
	}


	AssetManager::~AssetManager()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetManager...");
		delete mPregameAssetManager;
	}


	void AssetManager::initAssets()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Initializing AssetLoaders...");
	}


	void AssetManager::loadAssets()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Loading AssetLoaders...");
	}


	PregameAssetLoader* AssetManager::getPregameAssetLoader() const
	{
		return mPregameAssetManager;
	}
}