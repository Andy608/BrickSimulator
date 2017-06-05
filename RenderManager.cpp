#include "RenderManager.h"
#include "ShaderList.h"
#include "ResourceShaderProgram.h"
#include "GameSettingsHandler.h"
#include "Camera.h"
#include "Logger.h"
#include <assimp\Importer.hpp>

namespace Bountive
{
	Logger RenderManager::logger = Logger("RenderManager", Logger::Level::LEVEL_ALL);
	GLint RenderManager::renderScreenWidth;
	GLint RenderManager::renderScreenHeight;

	void RenderManager::updateRenderScreenSize(GLint width, GLint height)
	{
		renderScreenWidth = width;
		renderScreenHeight = height;
		Camera::updateProjectionMatrix(renderScreenWidth, renderScreenHeight);
	}


	RenderManager::RenderManager() :
		mCamera(new Camera(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0))),
		mGuiRenderer(new GuiRenderer(*this)),
		mModelRenderer(new ModelRenderer(*this))
	{
		logger.log(Logger::Level::LEVEL_INFO, "Creating RenderManager...");
	}


	RenderManager::~RenderManager()
	{
		logger.log(Logger::Level::LEVEL_INFO, "Deleting RenderManager...");
		delete mCamera;
		delete mGuiRenderer;
		delete mModelRenderer;
	}


	void RenderManager::setShader(ResourceShaderProgram* shader)
	{
		mActiveShaderProgram = shader;
	}


	const ResourceShaderProgram& RenderManager::getActiveShader() const
	{
		return *mActiveShaderProgram;
	}


	GuiRenderer& RenderManager::getGuiRenderer() const
	{
		return *mGuiRenderer;
	}


	ModelRenderer& RenderManager::getModelRenderer() const
	{
		return *mModelRenderer;
	}


	Camera& RenderManager::getCamera() const
	{
		return *mCamera;
	}
}