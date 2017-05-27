#include "PregameAssetLoader.h"
#include "DirectoryUtil.h"
#include "AssetImage.h"
#include "AssetMeshGui.h"
#include "AssetShader.h"
#include "AssetShaderProgram.h"
#include "Logger.h"

namespace Bountive
{
	Logger PregameAssetLoader::logger = Logger("PregameAssetLoader", Logger::Level::LEVEL_ALL);

	PregameAssetLoader::PregameAssetLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating PregameAssetLoader...");
	}


	PregameAssetLoader::~PregameAssetLoader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting PregameAssetLoader...");
	}


	void PregameAssetLoader::initAssets()
	{
		mBountiveLogo = new AssetImage(L"bountive_logo", *DirectoryUtil::instance->mEXE_IMAGES, L"bountive_logo");
		mGuiMesh = new AssetMeshGui();

		addAsset(mBountiveLogo);
		addAsset(mGuiMesh);

		loadShaders();
	}


	void PregameAssetLoader::loadShaders()
	{
		mGuiVertexShader = new AssetShader(L"gui_vertex_shader", AssetShader::ShaderType::VERTEX, new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_vertex_shader", FileLocation::VS_SHADER_EXTENSION));
		mGuiFragmentShader = new AssetShader(L"gui_fragment_shader", AssetShader::ShaderType::FRAGMENT, new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_fragment_shader", FileLocation::FS_SHADER_EXTENSION));

		addAsset(mGuiVertexShader);
		addAsset(mGuiFragmentShader);
		
		mGuiShaderProgram = new AssetShaderProgram(L"gui_shader_program");
		mGuiShaderProgram->attachShader(mGuiVertexShader);
		mGuiShaderProgram->attachShader(mGuiFragmentShader);
		mGuiShaderProgram->compileProgram();

		addAsset(mGuiShaderProgram);
	}
}