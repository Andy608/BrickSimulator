#include "GuiResourceBundle.h"
#include "ResourceBundleTracker.h"
#include "DirectoryUtil.h"
#include "Logger.h"

namespace Bountive
{
	ResourceMeshGui* GuiResourceBundle::mGuiMesh = nullptr;
	ResourceTexture* GuiResourceBundle::mBountiveLogoTexture = nullptr;
	ResourceShader* GuiResourceBundle::mGuiVertexShader = nullptr;
	ResourceShader* GuiResourceBundle::mGuiFragmentShader = nullptr;
	ResourceShaderProgram* GuiResourceBundle::mGuiShaderProgram = nullptr;

	Logger GuiResourceBundle::logger = Logger("GuiResourceBundle", Logger::Level::LEVEL_ALL);

	GuiResourceBundle::GuiResourceBundle() :
		ResourceBundle(ResourceBundle::BundleID::GUI)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating GuiResourceBundle...");
	}


	GuiResourceBundle::~GuiResourceBundle()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting GuiResourceBundle...");

		if (mIsLoaded)
		{
			unloadResourceBundle();
		}
	}


	void GuiResourceBundle::loadResourceBundle()
	{
		if (mIsLoaded)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Cannot load GuiResourceBundle it is already loaded...");
			return;
		}

		logger.log(Logger::Level::LEVEL_DEBUG, "Loading GuiResourceBundle...");

		mGuiMesh = new ResourceMeshGui("mesh_gui");

		mBountiveLogoTexture = new ResourceTexture("texture_bountive_logo", *DirectoryUtil::instance->mEXE_IMAGES, L"bountive_logo");

		mGuiVertexShader = new ResourceShader("shader_vertex_gui", ResourceShader::ShaderType::VERTEX, 
			new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_vertex_shader", FileLocation::VS_SHADER_EXTENSION));
		
		mGuiFragmentShader = new ResourceShader("shader_fragment_gui", ResourceShader::ShaderType::FRAGMENT, 
			new FileLocation(DirectoryUtil::instance->mEXE_SHADERS, L"gui_fragment_shader", FileLocation::FS_SHADER_EXTENSION));

		mGuiShaderProgram = new ResourceShaderProgram("shader_program_gui");
		mGuiShaderProgram->attachShader(mGuiVertexShader);
		mGuiShaderProgram->attachShader(mGuiFragmentShader);

		mResourceList->push_back(mGuiMesh);
		mResourceList->push_back(mBountiveLogoTexture);
		mResourceList->push_back(mGuiVertexShader);
		mResourceList->push_back(mGuiFragmentShader);
		mResourceList->push_back(mGuiShaderProgram);

		ResourceBundle::loadResourceBundle();
	}


	void GuiResourceBundle::unloadResourceBundle()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Unloading GuiResourceBundle...");
		ResourceBundle::unloadResourceBundle();
	}
}