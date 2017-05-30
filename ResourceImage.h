#pragma once
#ifndef BOUNTIVE_RESOURCEIMAGE_H_
#define BOUNTIVE_RESOURCEIMAGE_H_

#include "Resource.h"
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class ResourceImage : public Resource
	{
	public:
		ResourceImage(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME);
		virtual ~ResourceImage();

		virtual GLboolean load();
		virtual void unload();

		const GLint& getWidth() const;
		const GLint& getHeight() const;

		GLubyte* getGLImageId() const;

	private:
		static Logger logger;

		const FileLocation mFILE_LOCATION;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mImageId;
	};
}

#endif