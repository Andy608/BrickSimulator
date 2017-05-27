#include "AssetShader.h"
#include "FileReader.h"
#include "StringUtil.h"
#include "Logger.h"

namespace Bountive
{
	const GLint AssetShader::SIZE = 1;
	const GLint AssetShader::ERROR_LOG_SIZE = 512;
	Logger AssetShader::logger = Logger("AssetShader", Logger::Level::LEVEL_ALL);

	AssetShader::AssetShader(const std::wstring ASSET_ID, const ShaderType& SHADER_TYPE, FileLocation* shaderPath) :
		Asset(ASSET_ID),
		mSHADER_TYPE(SHADER_TYPE),
		mShaderPath(shaderPath),
		mFileReader(new FileReader())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetShader...");
		extractFromFile();
		compile();
		mIsLoaded = GL_TRUE;
	}


	AssetShader::~AssetShader()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetShader...");
		glDeleteShader(mShaderId);
		delete mShaderPath;
		delete mFileReader;
	}


	GLboolean AssetShader::load()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded AssetShader: " + mASSET_ID);
		return mIsLoaded;
	}


	void AssetShader::unload()
	{

	}


	void AssetShader::compile()
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


	const AssetShader::ShaderType& AssetShader::getShaderType() const
	{
		return mSHADER_TYPE;
	}


	const FileLocation& AssetShader::getShaderPath() const
	{
		return *mShaderPath;
	}


	const GLint& AssetShader::getGLShaderId() const
	{
		return mShaderId;
	}


	void AssetShader::extractFromFile()
	{
		mFileReader->getFileContents(*mShaderPath, mShaderCode);
	}
}