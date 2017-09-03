#include "ModelResourceBundle.h"
#include "DirectoryUtil.h"
#include "Logger.h"

namespace Bountive
{
	ModelBarrel* ModelResourceBundle::mModelBarrel = nullptr;
	ResourceShader* ModelResourceBundle::mModelVertexShader = nullptr;
	ResourceShader* ModelResourceBundle::mModelFragmentShader = nullptr;
	ResourceShaderProgram* ModelResourceBundle::mModelShaderProgram = nullptr;

	Logger ModelResourceBundle::logger = Logger("ModelResourceBundle", Logger::Level::LEVEL_ALL);

	ModelResourceBundle::ModelResourceBundle() :
		ResourceBundle(ResourceBundle::BundleID::MODEL)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ModelResourceBundle...");
	}


	ModelResourceBundle::~ModelResourceBundle()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ModelResourceBundle...");

		if (mIsLoaded)
		{
			unloadResourceBundle();
		}
	}


	void ModelResourceBundle::loadResourceBundle()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Cannot load ModelResourceBundle it is already loaded...");
			return;
		}

		logger.log(Logger::Level::LEVEL_DEBUG, "Loading ModelResourceBundle...");

		mModelBarrel = new ModelBarrel();

		mModelVertexShader = new ResourceShader("shader_vertex_model", ResourceShader::EnumShaderType::VERTEX,
			new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"model_vertex_shader", FileLocation::VS_SHADER_EXTENSION));

		mModelFragmentShader = new ResourceShader("shader_fragment_model", ResourceShader::EnumShaderType::FRAGMENT,
			new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"model_fragment_shader", FileLocation::FS_SHADER_EXTENSION));

		mModelShaderProgram = new ResourceShaderProgram("shader_program_model");
		mModelShaderProgram->attachShader(mModelVertexShader);
		mModelShaderProgram->attachShader(mModelFragmentShader);

		mResourceList->push_back(mModelBarrel);
		mResourceList->push_back(mModelVertexShader);
		mResourceList->push_back(mModelFragmentShader);
		mResourceList->push_back(mModelShaderProgram);

		ResourceBundle::loadResourceBundle();
	}


	void ModelResourceBundle::unloadResourceBundle()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Unloading ModelResourceBundle...");
		ResourceBundle::unloadResourceBundle();
	}
}