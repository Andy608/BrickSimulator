#include <soil\SOIL.h>
#include <shlobj.h>
#include "AssetImage.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger AssetImage::logger = Logger("AssetImage", Logger::Level::LEVEL_ALL);

	AssetImage::AssetImage(const std::wstring ASSET_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME) :
		Asset(ASSET_ID),
		mFILE_LOCATION(FileLocation(&DIRECTORY, FILE_NAME, FileLocation::PNG_EXTENSION))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating AssetImage: " + mFILE_LOCATION.getFileName());
	}


	AssetImage::~AssetImage()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting AssetImage: " + mFILE_LOCATION.getFileName());
		unload();
	}


	GLboolean AssetImage::load()
	{
		mImage = SOIL_load_image(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, SOIL_LOAD_RGBA);//stbi_load(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, STBI_rgb_alpha);

		if (mImage != nullptr)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded AssetImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Failed to load AssetImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_FALSE;
		}
		
		return mIsLoaded;
	}


	void AssetImage::unload()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Unloading AssetImage: " + mFILE_LOCATION.getFileName());
			SOIL_free_image_data(mImage);
			mIsLoaded = GL_FALSE;
		}
	}


	const GLint& AssetImage::getWidth() const
	{
		return mWidth;
	}


	const GLint& AssetImage::getHeight() const
	{
		return mHeight;
	}


	GLubyte* AssetImage::getGLImage() const
	{
		return mImage;
	}
}