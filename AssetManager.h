#pragma once
#ifndef BOUNTIVE_ASSETMANAGER_H_
#define BOUNTIVE_ASSETMANAGER_H_

#include "PregameAssetLoader.h"

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

		PregameAssetLoader* getPregameAssetLoader() const;

	private:
		static Logger logger;
		PregameAssetLoader* mPregameAssetManager;
		//AssetLoader* mGUIAssetLoader;
		GLint mTotalPercentLoaded;
	};
}

#endif