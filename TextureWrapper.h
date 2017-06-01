#pragma once
#ifndef BOUNTIVE_TEXTUREWRAPPER_H_
#define BOUNTIVE_TEXTUREWRAPPER_H_

#include "GLWrapper.h"
#include "ResourceTexture.h"

namespace Bountive
{
	class TextureWrapper : public GLWrapper
	{
	public:
		enum class WrapStyle : GLint
		{
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};


		enum class MinFilter : GLint
		{
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class MaxFilter : GLint
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR
		};

		TextureWrapper(ResourceTexture* image);
		virtual ~TextureWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		void setTexture(ResourceTexture* image);

		void setWrapStyleS(const WrapStyle& wrapStyleS);
		void setWrapStyleT(const WrapStyle& wrapStyleT);

		void setMinifyFilter(const MinFilter& minifyFilter);
		void setMaxifyFilter(const MaxFilter& maxifyFilter);

		void generateGLtexture();

		ResourceTexture* getResourceTexture() const;

		const WrapStyle& getWrapStyleS() const;
		const WrapStyle& getWrapStyleT() const;

		const MinFilter& getMinifyFilter() const;
		const MaxFilter& getMaxifyFilter() const;

	private:
		ResourceTexture* mTexture;

		WrapStyle mWrapStyleS;
		WrapStyle mWrapStyleT;

		MinFilter mMinifyFilter;
		MaxFilter mMaxifyFilter;

		virtual void createId();
	};
}

#endif