#pragma once
#ifndef BOUNTIVE_ASSETMANAGER_H_
#define BOUNTIVE_ASSETMANAGER_H_

#include "AssetLoader.h"

namespace Bountive
{
	class Logger;

	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		void initAssets();
		void loadAssets();

	private:
		static Logger logger;
		AssetLoader* mPregameAssetManager;
		//AssetLoader* mGUIAssetLoader;
		GLint mTotalPercentLoaded;
	};
}

#endif