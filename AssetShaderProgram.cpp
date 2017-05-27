#include "AssetShaderProgram.h"
#include "Logger.h"

namespace Bountive
{
	const GLint AssetShaderProgram::ERROR_LOG_SIZE = 512;
	Logger AssetShaderProgram::logger = Logger("AssetShaderProgram", Logger::Level::LEVEL_ALL);


	AssetShaderProgram::AssetShaderProgram(const std::wstring ASSET_ID) :
		Asset(ASSET_ID),
		mActiveShaders(std::vector<AssetShader*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetShaderProgram...");
		mIsLoaded = GL_TRUE;
	}


	AssetShaderProgram::~AssetShaderProgram()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetShaderProgram...");
		glDeleteProgram(mProgramId);
		mActiveShaders.clear();
	}


	GLboolean AssetShaderProgram::load()
	{
		return mIsLoaded;
	}


	void AssetShaderProgram::unload()
	{

	}


	void AssetShaderProgram::use() const
	{
		glUseProgram(mProgramId);
	}


	void AssetShaderProgram::attachShader(AssetShader* shader)
	{
		mActiveShaders.push_back(shader);
	}


	const GLint& AssetShaderProgram::getProgramId() const
	{
		return mProgramId;
	}


	void AssetShaderProgram::compileProgram()
	{
		mProgramId = glCreateProgram();

		for (GLuint i = 0; i < mActiveShaders.size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, L"Attaching shader: " + mActiveShaders.at(i)->getAssetId());
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