#include "AssetLoader.h"
#include "Logger.h"

namespace Bountive
{
	Logger AssetLoader::logger = Logger("AssetLoader", Logger::Level::LEVEL_ALL);

	AssetLoader::AssetLoader() :
		mAssetList(new std::vector<Asset*>()),
		mPercentLoaded(0)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetLoader...");
	}


	AssetLoader::~AssetLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetLoader...");
		unloadAssets();
		clearAssetList();
		delete mAssetList;
	}


	void AssetLoader::addAsset(Asset* asset)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Adding asset: " + asset->getAssetId());
		mAssetList->push_back(asset);
	}

	void AssetLoader::loadAssets()
	{
		//Look into using another thread for asset loader
		for (GLuint i = 0; i < mAssetList->size(); ++i)
		{
			mAssetList->at(i)->load();
			mPercentLoaded = ((i + 1) / mAssetList->size()) * 100.0f;
			logger.log(Logger::Level::LEVEL_DEBUG, L"Loaded asset: " + mAssetList->at(i)->getAssetId() + L" Percent Loaded = " + std::to_wstring(mPercentLoaded));
		}
	}


	void AssetLoader::unloadAssets()
	{
		for (GLuint i = 0; i < mAssetList->size(); ++i)
		{
			mAssetList->at(i)->unload();
			mPercentLoaded = (((mAssetList->size() - 1) - i) / mAssetList->size()) * 100.0f;
			logger.log(Logger::Level::LEVEL_DEBUG, L"Unloaded asset: " + mAssetList->at(i)->getAssetId() + L" Percent Loaded = " + std::to_wstring(mPercentLoaded));
		}
	}


	void AssetLoader::clearAssetList()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "AssetList has " + std::to_string(mAssetList->size()) + " assets before clearing...");

		for (GLuint i = 0; i < mAssetList->size(); ++i)
		{
			if (mAssetList->at(i) != nullptr)
			{
				logger.log(Logger::Level::LEVEL_DEBUG, mAssetList->at(i)->getAssetId() + L" cleared and deleted!");
				delete mAssetList->at(i);
			}
		}

		mAssetList->clear();
		logger.log(Logger::Level::LEVEL_DEBUG, "AssetList has " + std::to_string(mAssetList->size()) + " assets after clearing.");
	}
}