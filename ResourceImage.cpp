#include <soil\SOIL.h>
#include <shlobj.h>
#include "ResourceImage.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceImage::logger = Logger("ResourceImage", Logger::Level::LEVEL_ALL);

	ResourceImage::ResourceImage(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME) :
		Resource(RESOURCE_ID),
		mFILE_LOCATION(FileLocation(&DIRECTORY, FILE_NAME, FileLocation::PNG_EXTENSION))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating ResourceImage: " + mFILE_LOCATION.getFileName());
	}


	ResourceImage::~ResourceImage()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting ResourceImage: " + mFILE_LOCATION.getFileName());
		unload();
	}


	GLboolean ResourceImage::load()
	{
		mImageId = SOIL_load_image(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, SOIL_LOAD_RGBA);

		if (mImageId != nullptr)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded ResourceImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Failed to load ResourceImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_FALSE;
		}
		
		return mIsLoaded;
	}


	void ResourceImage::unload()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Unloading ResourceImage: " + mFILE_LOCATION.getFileName());
			SOIL_free_image_data(mImageId);
			mIsLoaded = GL_FALSE;
		}
	}


	const GLint& ResourceImage::getWidth() const
	{
		return mWidth;
	}


	const GLint& ResourceImage::getHeight() const
	{
		return mHeight;
	}


	GLubyte* ResourceImage::getGLImageId() const
	{
		return mImageId;
	}
}