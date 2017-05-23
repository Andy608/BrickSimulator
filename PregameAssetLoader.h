#pragma once
#ifndef BOUNTIVE_PREGAMEASSETLOADER_H_
#define BOUNTIVE_PREGAMEASSETLOADER_H_

#include "AssetLoader.h"

namespace Bountive
{
	class Logger;

	class PregameAssetLoader : public AssetLoader
	{
	public:
		PregameAssetLoader();
		~PregameAssetLoader();

		virtual void initAssets();
			
	private:
		static Logger logger;
};

}

#endif