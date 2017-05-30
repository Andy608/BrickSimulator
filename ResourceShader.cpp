#include "ResourceShader.h"
#include "FileReader.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	const GLint ResourceShader::SIZE = 1;
	const GLint ResourceShader::ERROR_LOG_SIZE = 512;
	Logger ResourceShader::logger = Logger("ResourceShader", Logger::Level::LEVEL_ALL);

	ResourceShader::ResourceShader(const std::string RESOURCE_ID, const ShaderType& SHADER_TYPE, FileLocation* shaderPath) :
		Resource(RESOURCE_ID),
		mSHADER_TYPE(SHADER_TYPE),
		mShaderPath(shaderPath),
		mFileReader(new FileReader())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceShader...");
		extractFromFile();
		compile();
		mIsLoaded = GL_TRUE;
	}


	ResourceShader::~ResourceShader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceShader...");
		glDeleteShader(mShaderId);
		delete mShaderPath;
		delete mFileReader;
	}


	GLboolean ResourceShader::load()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Successfully loaded AssetShader: " + mRESOURCE_ID);
		return mIsLoaded;
	}


	void ResourceShader::unload()
	{

	}


	void ResourceShader::compile()
	{
		switch (mSHADER_TYPE)
		{
		case ShaderType::VERTEX:	mShaderId = glCreateShader(GL_VERTEX_SHADER);
									break;
		default:					mShaderId = glCreateShader(GL_FRAGMENT_SHADER);
									break;
		}

		const GLchar* shaderCode = mShaderCode.c_str();
		GLint compiled;
		GLchar errorLog[ERROR_LOG_SIZE];

		glShaderSource(mShaderId, SIZE, &shaderCode, NULL);
		glCompileShader(mShaderId);
		glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			glGetShaderInfoLog(mShaderId, ERROR_LOG_SIZE, NULL, errorLog);
			logger.log(Logger::Level::LEVEL_ERROR, "Could not compile shader: " + std::string(errorLog));
		}
		else
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Shader successfully compiled!");
		}

		logger.log(Logger::Level::LEVEL_ERROR, mShaderCode);
	}


	const ResourceShader::ShaderType& ResourceShader::getShaderType() const
	{
		return mSHADER_TYPE;
	}


	const FileLocation& ResourceShader::getShaderPath() const
	{
		return *mShaderPath;
	}


	const GLint& ResourceShader::getGLShaderId() const
	{
		return mShaderId;
	}


	void ResourceShader::extractFromFile()
	{
		mFileReader->getFileContents(*mShaderPath, mShaderCode);
	}
}