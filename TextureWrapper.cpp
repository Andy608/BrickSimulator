#include "TextureWrapper.h"

namespace Bountive
{
	TextureWrapper::TextureWrapper(ResourceImage* image) :
		mImage(image),
		mWrapStyleS(WrapStyle::REPEAT),
		mWrapStyleT(WrapStyle::REPEAT),
		mMinifyFilter(MinFilter::NEAREST_MIPMAP_NEAREST),
		mMaxifyFilter(MaxFilter::NEAREST)
	{
		createId();
	}


	TextureWrapper::~TextureWrapper()
	{

	}


	void TextureWrapper::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mId);
	}


	void TextureWrapper::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void TextureWrapper::setImage(ResourceImage* image)
	{
		mImage = image;
	}


	void TextureWrapper::setWrapStyleS(const WrapStyle& wrapStyleS)
	{
		mWrapStyleS = wrapStyleS;
	}


	void TextureWrapper::setWrapStyleT(const WrapStyle& wrapStyleT)
	{
		mWrapStyleT = wrapStyleT;
	}


	void TextureWrapper::setMinifyFilter(const MinFilter& minifyFilter)
	{
		mMinifyFilter = minifyFilter;
	}


	void TextureWrapper::setMaxifyFilter(const MaxFilter& maxifyFilter)
	{
		mMaxifyFilter = maxifyFilter;
	}


	void TextureWrapper::generateGLtexture()
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(mWrapStyleS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(mWrapStyleT));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(mMinifyFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(mMaxifyFilter));

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage->getWidth(), mImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mImage->getGLImageId());
		
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}


	ResourceImage* TextureWrapper::getImage() const
	{
		return mImage;
	}


	const TextureWrapper::WrapStyle& TextureWrapper::getWrapStyleS() const
	{
		return mWrapStyleS;
	}


	const TextureWrapper::WrapStyle& TextureWrapper::getWrapStyleT() const
	{
		return mWrapStyleT;
	}


	const TextureWrapper::MinFilter& TextureWrapper::getMinifyFilter() const
	{
		return mMinifyFilter;
	}


	const TextureWrapper::MaxFilter& TextureWrapper::getMaxifyFilter() const
	{
		return mMaxifyFilter;
	}


	void TextureWrapper::createId()
	{
		glGenTextures(SIZE, &mId);
	}
}