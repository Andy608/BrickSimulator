#include "ResourceBundle.h"
#include "Logger.h"

namespace Bountive
{
	GLint ResourceBundle::FULLY_LOADED = 100;
	Logger ResourceBundle::logger = Logger("ResourceBundle", Logger::Level::LEVEL_ALL);

	ResourceBundle::ResourceBundle(const ResourceBundle::BundleID& PACKAGE_ID) :
		mPACKAGE_ID(PACKAGE_ID),
		mResourceList(new std::vector<Resource*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceBundle...");
		logger.log(Logger::Level::LEVEL_DEBUG, "HELLO: " + std::to_string(static_cast<GLint>(mPACKAGE_ID)));
	}


	ResourceBundle::~ResourceBundle()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceBundle...");
		delete mResourceList;
	}

	//call this method to load each resource in the list.
	void ResourceBundle::loadResourceBundle()
	{
		//Look into using another thread for asset loader
		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			mResourceList->at(i)->load();
			mPercentLoaded = ((i + 1) / static_cast<GLfloat>(mResourceList->size())) * static_cast<GLfloat>(FULLY_LOADED);

			logger.log(Logger::Level::LEVEL_DEBUG, "Loaded: " + mResourceList->at(i)->getResourceId() +
				" Percent Loaded = " + std::to_string(mPercentLoaded));
		}

		mIsLoaded = GL_TRUE;
	}

	//Delete all the resources in the bundle
	void ResourceBundle::unloadResourceBundle()
	{
		GLuint originalSize = mResourceList->size();
		GLuint counter = 0; 
		for (GLuint i = 0; i < mResourceList->size(); ++i, ++counter)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Deleted: " + mResourceList->at(i)->getResourceId() +
				" Percent Loaded = " + std::to_string(mPercentLoaded));

			delete mResourceList->at(i);
			mResourceList->erase(mResourceList->begin() + i);
			--i;
			mPercentLoaded = (((originalSize - 1) - counter) / originalSize) * static_cast<GLfloat>(FULLY_LOADED);
		}

		mResourceList->clear();
		mIsLoaded = GL_FALSE;
	}


	Resource* ResourceBundle::findResource(std::string RESOURCE_ID) const
	{
		for (GLuint i = 0; i < mResourceList->size(); ++i)
		{
			if (mResourceList->at(i)->getResourceId().compare(RESOURCE_ID))
			{
				return mResourceList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Could not find resource with id: " + RESOURCE_ID + " in bundle.");
		return nullptr;
	}


	const GLboolean& ResourceBundle::isLoaded() const
	{
		return mIsLoaded;
	}
}