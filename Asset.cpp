#include "Asset.h"

namespace Bountive
{
	Asset::Asset(const FileDirectory& DIRECTORY, const std::wstring FILE_NAME, const std::wstring& FILE_EXTENSION) :
		mFILE_LOCATION(FileLocation(&DIRECTORY, FILE_NAME, FILE_EXTENSION)),
		mASSET_ID(FILE_NAME),
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