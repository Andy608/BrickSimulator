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


	void ModelRenderer::render(const GLdouble& DELTA_TIME, const std::vector<Entity*>& MODEL_LIST, const ResourceShaderProgram& activeShaderProgram)
	{
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		activeShaderProgram.use();

		activeShaderProgram.loadMat4("viewMatrixUniform", GL_FALSE, mRenderManager.getCamera().getViewMatrixPtr());
		activeShaderProgram.loadMat4("projectionMatrixUniform", GL_FALSE, mRenderManager.getCamera().getPerspectiveMatrixPtr());

		for (GLuint i = 0; i < MODEL_LIST.size(); ++i)
		{
			activeShaderProgram.loadMat4("transformUniform", GL_FALSE, MODEL_LIST.at(i)->getTransform()->getTransformationMatrixPtr());
			MODEL_LIST.at(i)->getModel()->render(DELTA_TIME);
		}

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
	}

}