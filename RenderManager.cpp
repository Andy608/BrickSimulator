#include "RenderManager.h"
#include "ShaderList.h"
#include "ResourceShaderProgram.h"
#include "Logger.h"

namespace Bountive
{
	Logger RenderManager::logger = Logger("RenderManager", Logger::Level::LEVEL_ALL);

	RenderManager::RenderManager() :
		mGuiRenderer(new GuiRenderer(*this))
	{
		logger.log(Logger::Level::LEVEL_INFO, "Creating RenderManager...");
	}


	RenderManager::~RenderManager()
	{
		logger.log(Logger::Level::LEVEL_INFO, "Deleting RenderManager...");
		delete mGuiRenderer;
	}


	void RenderManager::setShader(ResourceShaderProgram* shader)
	{
		mActiveShaderProgram = shader;
	}


	GLuint RenderManager::getUniformID(std::string uniformName) const
	{
		return glGetUniformLocation(mActiveShaderProgram->getProgramID(), uniformName.c_str());
	}


	void RenderManager::loadInt1(std::string uniformName, GLint integer) const
	{
		glUniform1i(getUniformID(uniformName), integer);
	}


	void RenderManager::loadMat4(std::string uniformName, GLboolean transpose, const GLfloat* matrixPtr) const
	{
		glUniformMatrix4fv(getUniformID(uniformName), 1, transpose ? GL_TRUE : GL_FALSE, matrixPtr);
	}


	const ResourceShaderProgram& RenderManager::getActiveShader() const
	{
		return *mActiveShaderProgram;
	}


	GuiRenderer& RenderManager::getGuiRenderer() const
	{
		return *mGuiRenderer;
	}
}