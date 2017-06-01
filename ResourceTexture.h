#pragma once
#ifndef BOUNTIVE_RESOURCETEXTURE_H_
#define BOUNTIVE_RESOURCETEXTURE_H_

#include "Resource.h"
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class ResourceTexture : public Resource
	{
	public:
		ResourceTexture(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME);
		virtual ~ResourceTexture();

		virtual void load();
		virtual void unload();

		const GLint& getWidth() const;
		const GLint& getHeight() const;

		GLubyte* getGLTextureID() const;

	private:
		static Logger logger;

		const FileLocation mFILE_LOCATION;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mTextureID;
	};
}

#endif