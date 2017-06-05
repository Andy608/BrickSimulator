#include "ModelRenderer.h"
#include "RenderManager.h"
#include "ResourceShaderProgram.h"
#include "Camera.h"
#include "Logger.h"
#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Bountive
{
	Logger ModelRenderer::logger = Logger("ModelRenderer", Logger::Level::LEVEL_ALL);

	ModelRenderer::ModelRenderer(RenderManager& renderManager) :
		Renderer(renderManager)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ModelRenderer...");
	}


	ModelRenderer::~ModelRenderer()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ModelRenderer...");
	}


	void ModelRenderer::render(const GLdouble& DELTA_TIME, const std::vector<ResourceModel*>& MODEL_LIST, const ResourceShaderProgram& activeShaderProgram)
	{
		glEnable(GL_DEPTH_TEST);

		activeShaderProgram.use();

		activeShaderProgram.loadMat4("viewMatrixUniform", GL_FALSE, mRenderManager.getCamera().getViewMatrixPtr());
		activeShaderProgram.loadMat4("projectionMatrixUniform", GL_FALSE, mRenderManager.getCamera().getPerspectiveMatrixPtr());
		activeShaderProgram.loadMat4("transformUniform", GL_FALSE, glm::value_ptr(glm::mat4x4()));

		for (GLuint i = 0; i < MODEL_LIST.size(); ++i)
		{
			MODEL_LIST.at(i)->render(DELTA_TIME, activeShaderProgram);
		}

		glDisable(GL_DEPTH_TEST);
	}

}