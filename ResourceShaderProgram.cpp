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
		mIsLoaded = GL_TRUE;
	}


	ResourceShaderProgram::~ResourceShaderProgram()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceShaderProgram...");
		glDeleteProgram(mProgramId);
		mActiveShaders.clear();
	}


	GLboolean ResourceShaderProgram::load()
	{
		return mIsLoaded;
	}


	void ResourceShaderProgram::unload()
	{

	}


	void ResourceShaderProgram::use() const
	{
		glUseProgram(mProgramId);
	}


	void ResourceShaderProgram::attachShader(ResourceShader* shader)
	{
		mActiveShaders.push_back(shader);
	}


	const GLint& ResourceShaderProgram::getProgramId() const
	{
		return mProgramId;
	}


	void ResourceShaderProgram::compileProgram()
	{
		mProgramId = glCreateProgram();

		for (GLuint i = 0; i < mActiveShaders.size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Attaching shader: " + mActiveShaders.at(i)->getResourceId());
			glAttachShader(mProgramId, mActiveShaders.at(i)->getGLShaderId());
		}

		glLinkProgram(mProgramId);

		GLint compiled;
		GLchar errorLog[ERROR_LOG_SIZE];

		glGetProgramiv(mProgramId, GL_LINK_STATUS, &compiled);
		
		if (!compiled)
		{
			glGetProgramInfoLog(mProgramId, ERROR_LOG_SIZE, NULL, errorLog);
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Successfully compiled shader program.");
		}
	}
}