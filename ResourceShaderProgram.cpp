#include "ResourceShaderProgram.h"
#include "Logger.h"

namespace Bountive
{
	const GLint ResourceShaderProgram::ERROR_LOG_SIZE = 512;
	Logger ResourceShaderProgram::logger = Logger("ResourceShaderProgram", Logger::Level::LEVEL_ALL);

	ResourceShaderProgram::ResourceShaderProgram(const std::string RESOURCE_ID) :
		Resource(RESOURCE_ID),
		mActiveShaders(std::vector<ResourceShader*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceShaderProgram...");
		mIsLoaded = GL_FALSE;
	}


	ResourceShaderProgram::~ResourceShaderProgram()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceShaderProgram...");

		if (mIsLoaded)
		{
			unload();
		}
	}


	void ResourceShaderProgram::load()
	{
		compileProgram();
	}


	void ResourceShaderProgram::unload()
	{
		glDeleteProgram(mProgramID);
		mActiveShaders.clear();
	}


	void ResourceShaderProgram::use() const
	{
		for (GLuint i = 0; i < mActiveShaders.size(); ++i)
		{
			if (!mActiveShaders.at(i)->isLoaded())
			{
				logger.log(Logger::Level::LEVEL_DEBUG, "Error when trying to use shader program. Shader: " + mActiveShaders.at(i)->getResourceId() + " is not loaded.");
				return;
			}
		}

		glUseProgram(mProgramID);
	}


	void ResourceShaderProgram::attachShader(ResourceShader* shader)
	{
		mActiveShaders.push_back(shader);
	}


	const GLint& ResourceShaderProgram::getProgramID() const
	{
		return mProgramID;
	}


	void ResourceShaderProgram::compileProgram()
	{
		mProgramID = glCreateProgram();

		for (GLuint i = 0; i < mActiveShaders.size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Attaching shader: " + mActiveShaders.at(i)->getResourceId());
			glAttachShader(mProgramID, mActiveShaders.at(i)->getGLShaderId());
		}

		glLinkProgram(mProgramID);

		GLint compiled;
		GLchar errorLog[ERROR_LOG_SIZE];

		glGetProgramiv(mProgramID, GL_LINK_STATUS, &compiled);

		if (!compiled)
		{
			glGetProgramInfoLog(mProgramID, ERROR_LOG_SIZE, NULL, errorLog);
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Successfully compiled shader program.");
		}
	}


	GLuint ResourceShaderProgram::getUniformID(std::string uniformName) const
	{
		return glGetUniformLocation(mProgramID, uniformName.c_str());
	}


	void ResourceShaderProgram::loadInt1(std::string uniformName, GLint integer) const
	{
		glUniform1i(getUniformID(uniformName), integer);
	}


	void ResourceShaderProgram::loadFloat1(std::string uniformName, GLfloat floatingPoint) const
	{
		glUniform1f(getUniformID(uniformName), floatingPoint);
	}


	void ResourceShaderProgram::loadMat4(std::string uniformName, GLboolean transpose, const GLfloat* matrixPtr) const
	{
		glUniformMatrix4fv(getUniformID(uniformName), 1, transpose ? GL_TRUE : GL_FALSE, matrixPtr);
	}
}