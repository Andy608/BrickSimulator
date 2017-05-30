#include "StartupResourceLoader.h"
#include "DirectoryUtil.h"
#include "ResourceImage.h"
#include "ResourceShader.h"
#include "ResourceShaderProgram.h"
#include "MeshGui.h"
#include "Logger.h"

namespace Bountive
{
	Logger StartupResourceLoader::logger = Logger("StartupResourceLoader", Logger::Level::LEVEL_ALL);

	StartupResourceLoader::StartupResourceLoader() :
		ResourceLoader(ResourceLoader::ResourcePackageId::START_UP)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating StartupResourceLoader...");
	}


	StartupResourceLoader::~StartupResourceLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting StartupResourceLoader...");
	}


	void StartupResourceLoader::initResources()
	{
		mBountiveLogo = new ResourceImage("bountive_logo", *DirectoryUtil::instance->mEXE_IMAGES, L"bountive_logo");
		mGuiMesh = new MeshGui("mesh_bountive_logo");

		addResource(mBountiveLogo);
		addResource(mGuiMesh);

		loadShaders();
	}


	void StartupResourceLoader::loadShaders()
	{
		mGuiVertexShader = new ResourceShader("gui_vertex_shader", ResourceShader::ShaderType::VERTEX, new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_vertex_shader", FileLocation::VS_SHADER_EXTENSION));
		mGuiFragmentShader = new ResourceShader("gui_fragment_shader", ResourceShader::ShaderType::FRAGMENT, new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_fragment_shader", FileLocation::FS_SHADER_EXTENSION));

		addResource(mGuiVertexShader);
		addResource(mGuiFragmentShader);
		
		mGuiShaderProgram = new ResourceShaderProgram("gui_shader_program");
		mGuiShaderProgram->attachShader(mGuiVertexShader);
		mGuiShaderProgram->attachShader(mGuiFragmentShader);
		mGuiShaderProgram->compileProgram();

		addResource(mGuiShaderProgram);
	}
}