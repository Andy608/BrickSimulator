#pragma once
#ifndef BOUNTIVE_ASSETLOADER_H_
#define BOUNTIVE_ASSETLOADER_H_

#include <vector>
#include "Asset.h"

namespace Bountive
{
	class Logger;

	class AssetLoader
	{
	public:
		AssetLoader();
		virtual ~AssetLoader();

		virtual void initAssets() = 0;
		
		void addAsset(Asset* asset);

		void loadAssets();
		void unloadAssets();

		void clearAssetList();

	private:
		static Logger logger;
		std::vector<Asset*>* mAssetList;
		GLfloat mPercentLoaded;
	};
}

#endif