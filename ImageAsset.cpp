#include <soil\SOIL.h>
#include <shlobj.h>
#include "ImageAsset.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger ImageAsset::logger = Logger("ImageAsset", Logger::Level::LEVEL_ALL);

	ImageAsset::ImageAsset(const FileDirectory& DIRECTORY, const std::wstring IMAGE_NAME) :
		Asset(DIRECTORY, IMAGE_NAME, FileLocation::PNG_EXTENSION)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating ImageAsset: " + mFILE_LOCATION.getFileName());
	}


	ImageAsset::~ImageAsset()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting ImageAsset: " + mFILE_LOCATION.getFileName());
	}


	GLboolean ImageAsset::load()
	{
		mImageHandle = SOIL_load_image(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, SOIL_LOAD_RGBA);//stbi_load(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, STBI_rgb_alpha);

		if (mImageHandle != nullptr)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded ImageAsset: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Failed to load ImageAsset: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_FALSE;
		}
		
		return mIsLoaded;
	}


	void ImageAsset::unload()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Unloading ImageAsset: " + mFILE_LOCATION.getFileName());
		SOIL_free_image_data(mImageHandle);
		//stbi_image_free(mImageHandle);
	}


	const GLint& ImageAsset::getWidth() const
	{
		return mWidth;
	}


	const GLint& ImageAsset::getHeight() const
	{
		return mHeight;
	}
}