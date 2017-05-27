#pragma once
#ifndef BOUNTIVE_ASSET_H_
#define BOUNTIVE_ASSET_H_

#include <string>
#include <glew.h>

namespace Bountive
{
	class Asset
	{
	public:
		Asset(const std::wstring FILE_NAME);
		virtual ~Asset();

		virtual GLboolean load() = 0;
		virtual void unload() = 0;
		
		const std::wstring getAssetId() const;
		const GLboolean& isLoaded() const;

	protected:
		const std::wstring mASSET_ID;
		GLboolean mIsLoaded;
	};
}

#endif