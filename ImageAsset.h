#pragma once
#ifndef BOUNTIVE_IMAGEASSET_H_
#define BOUNTIVE_IMAGEASSET_H_

#include "Asset.h"
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class ImageAsset : public Asset
	{
	public:
		ImageAsset(const FileDirectory& DIRECTORY, const std::wstring IMAGE_NAME);
		virtual ~ImageAsset();

		virtual GLboolean load();
		virtual void unload();

		const GLint& getWidth() const;
		const GLint& getHeight() const;

	private:
		static Logger logger;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mImageHandle;
	};
}

#endif