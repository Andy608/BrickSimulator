#pragma once
#ifndef BOUNTIVE_ASSET_H_
#define BOUNTIVE_ASSET_H_

#include <string>
#include <glew.h>
#include "FileLocation.h"

namespace Bountive
{
	class Asset
	{
	public:
		Asset(const FileDirectory& DIRECTORY, const std::wstring FILE_NAME, const std::wstring& FILE_EXTENSION);
		virtual ~Asset();

		virtual GLboolean load() = 0;
		virtual void unload() = 0;
		
		const std::wstring getAssetId() const;
		const GLboolean& isLoaded() const;

	protected:
		const FileLocation mFILE_LOCATION;
		const std::wstring mASSET_ID;
		GLboolean mIsLoaded;
	};
}

#endif