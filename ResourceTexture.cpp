#include <soil\SOIL.h>
#include <shlobj.h>
#include "ResourceTexture.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceTexture::logger = Logger("ResourceTexture", Logger::Level::LEVEL_ALL);

	ResourceTexture::ResourceTexture(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME) :
		Resource(RESOURCE_ID),
		mFILE_LOCATION(FileLocation(&DIRECTORY, FILE_NAME, FileLocation::PNG_EXTENSION))
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Creating ResourceTexture: " + mFILE_LOCATION.getFileName());
	}


	ResourceTexture::~ResourceTexture()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Deleting ResourceTexture: " + mFILE_LOCATION.getFileName());
		unload();
	}


	void ResourceTexture::load()
	{
		mTextureID = SOIL_load_image(StringUtil::wtos(mFILE_LOCATION.getFullPath()).c_str(), &mWidth, &mHeight, &mColorChannels, SOIL_LOAD_RGBA);

		if (mTextureID != nullptr)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded ResourceImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_TRUE;
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Failed to load ResourceImage: " + mFILE_LOCATION.getFullPath());
			mIsLoaded = GL_FALSE;
		}
	}


	void ResourceTexture::unload()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Unloading ResourceImage: " + mFILE_LOCATION.getFileName());
			SOIL_free_image_data(mTextureID);
			mIsLoaded = GL_FALSE;
		}
	}


	const GLint& ResourceTexture::getWidth() const
	{
		return mWidth;
	}


	const GLint& ResourceTexture::getHeight() const
	{
		return mHeight;
	}


	GLubyte* ResourceTexture::getGLTextureID() const
	{
		return mTextureID;
	}
}