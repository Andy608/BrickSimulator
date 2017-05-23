#include "PregameAssetLoader.h"
#include "ImageAsset.h"
#include "DirectoryUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger PregameAssetLoader::logger = Logger("PregameAssetLoader", Logger::Level::LEVEL_ALL);

	PregameAssetLoader::PregameAssetLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating PregameAssetLoader...");
	}


	PregameAssetLoader::~PregameAssetLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting PregameAssetLoader...");
	}


	void PregameAssetLoader::initAssets()
	{
		addAsset(new ImageAsset(*DirectoryUtil::instance->mEXE_ASSETS, L"bountive_logo"));
	}
}