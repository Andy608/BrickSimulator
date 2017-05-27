#include "Asset.h"

namespace Bountive
{
	Asset::Asset(const std::wstring ASSET_ID) :
		mASSET_ID(ASSET_ID),
		mIsLoaded(GL_FALSE)
	{

	}


	Asset::~Asset()
	{

	}


	const std::wstring Asset::getAssetId() const
	{
		return mASSET_ID;
	}


	const GLboolean& Asset::isLoaded() const
	{
		return mIsLoaded;
	}
}