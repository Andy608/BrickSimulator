#pragma once
#ifndef BOUNTIVE_ASSETIMAGE_H_
#define BOUNTIVE_ASSETIMAGE_H_

#include "Asset.h"
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class AssetImage : public Asset
	{
	public:
		AssetImage(const std::wstring ASSET_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME);
		virtual ~AssetImage();

		virtual GLboolean load();
		virtual void unload();

		const GLint& getWidth() const;
		const GLint& getHeight() const;

		GLubyte* getGLImage() const;

	private:
		static Logger logger;

		const FileLocation mFILE_LOCATION;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mImage;
	};
}

#endif