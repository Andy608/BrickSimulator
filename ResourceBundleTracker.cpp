#include "ResourceBundleTracker.h"
//#include "GuiResourceBundle.h"
#include "ModelResourceBundle.h"
#include "ResourceBundle.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceBundleTracker::logger = Logger("ResourceBundleTracker", Logger::Level::LEVEL_ALL);

	ResourceBundleTracker::ResourceBundleTracker() :
		mBundleList(new std::vector<ResourceBundle*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceBundleTracker...");

		//mBundleList->push_back(new GuiResourceBundle());
		mBundleList->push_back(new ModelResourceBundle());
	}


	ResourceBundleTracker::~ResourceBundleTracker()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceBundleTracker...");

		for (GLuint i = 0; i < mBundleList->size(); ++i)
		{
			unloadBundle(mBundleList->at(i)->mPACKAGE_ID);
			delete mBundleList->at(i);
		}

		mBundleList->clear();
		delete mBundleList;
	}


	void ResourceBundleTracker::loadBundle(const ResourceBundle::BundleID& PACKAGE_ID)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Loading bundle..." + std::to_string(static_cast<GLint>(PACKAGE_ID)));
		
		for (GLuint i = 0; i < mBundleList->size(); ++i)
		{
			if (mBundleList->at(i)->mPACKAGE_ID == PACKAGE_ID)
			{
				logger.log(Logger::Level::LEVEL_DEBUG, "Bundle ID: " + std::to_string(static_cast<GLint>(mBundleList->at(i)->mPACKAGE_ID)));
				mBundleList->at(i)->loadResourceBundle();
				return;
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Cannot load resource bundle. No bundle with that package id.");
	}


	void ResourceBundleTracker::unloadBundle(const ResourceBundle::BundleID& PACKAGE_ID)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Unloaded bundle...");

		for (GLuint i = 0; i < mBundleList->size(); ++i)
		{
			if (mBundleList->at(i)->mPACKAGE_ID == PACKAGE_ID)
			{
				mBundleList->at(i)->unloadResourceBundle();
				return;
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "Cannot unload resource bundle. No bundle with that package id.");
	}


	ResourceBundle* ResourceBundleTracker::getBundle(const ResourceBundle::BundleID& PACKAGE_ID) const
	{
		for (GLuint i = 0; i < mBundleList->size(); ++i)
		{
			if (mBundleList->at(i)->mPACKAGE_ID == PACKAGE_ID)
			{
				return mBundleList->at(i);
			}
		}

		logger.log(Logger::Level::LEVEL_WARN, "No bundle with that package id.");

		return nullptr;
	}
}