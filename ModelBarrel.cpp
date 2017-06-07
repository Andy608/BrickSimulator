#include "ModelBarrel.h"
#include "Logger.h"
#include "ModelResourceBundle.h"
#include "DirectoryUtil.h"

namespace Bountive
{
	Logger ModelBarrel::logger = Logger("ModelBarrel", Logger::Level::LEVEL_ALL);

	ModelBarrel::ModelBarrel() :
		ResourceModel("model_barrel")
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ModelBarrel...");
	}


	ModelBarrel::~ModelBarrel()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ModelBarrel...");
	}


	void ModelBarrel::load()
	{
		FileLocation f = FileLocation(DirectoryUtil::instance->mEXE_MODELS, L"barrel", FileLocation::OBJ_EXTENSION);
		logger.log(Logger::Level::LEVEL_DEBUG, L"HELLO: " + f.getFullPath());
		ModelComponent* barrel = new ModelComponent(nullptr, new ResourceMesh("mesh_barrel", f));

		mModelComponents->push_back(barrel);

		ResourceModel::load();
	}


	void ModelBarrel::update(const GLdouble& DELTA_TIME)
	{

	}
}