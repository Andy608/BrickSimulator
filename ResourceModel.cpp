#include "ResourceModel.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceModel::logger = Logger("ResourceModel", Logger::Level::LEVEL_ALL);

	ResourceModel::ResourceModel(std::string RESOURCE_ID) :
		Resource(RESOURCE_ID),
		mModelComponents(new std::vector<ModelComponent*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceModel...");
	}


	ResourceModel::~ResourceModel()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceModel...");

		if (mIsLoaded)
		{
			unload();
		}

		delete mModelComponents;
	}


	void ResourceModel::load()
	{
		for (GLuint i = 0; i < mModelComponents->size(); ++i)
		{
			mModelComponents->at(i)->getMesh()->load();
		}
	}


	void ResourceModel::unload()
	{
		for (GLuint i = 0; i < mModelComponents->size(); ++i)
		{
			if (mModelComponents->at(i) != nullptr)
			{
				logger.log(Logger::Level::LEVEL_DEBUG, "Unloading ResourceModel: " + mRESOURCE_ID);
				mModelComponents->at(i)->getMesh()->unload();
			}
		}

		mModelComponents->clear();
	}

	void ResourceModel::render(const GLdouble& DELTA_TIME)
	{
		for (GLuint i = 0; i < mModelComponents->size(); ++i)
		{
			mModelComponents->at(i)->render(DELTA_TIME);
		}
	}
}