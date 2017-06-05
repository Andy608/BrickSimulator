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
		static const std::string DIFFUSE;
		static const std::string SPECULAR;

		enum class MaterialType : GLuint
		{
			DIFFUSE,
			SPECULAR
		};

		ResourceTexture(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME, const MaterialType& MATERIAL);
		virtual ~ResourceTexture();

		virtual void load();
		virtual void unload();

		const GLint& getWidth() const;
		const GLint& getHeight() const;

		GLfloat getAspectRatio() const;

		GLubyte* getSOILTextureID() const;

		const MaterialType& getMaterial() const;

	private:
		static Logger logger;

		const FileLocation mFILE_LOCATION;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mTextureID;
		MaterialType mMaterial;
	};
}

#endif