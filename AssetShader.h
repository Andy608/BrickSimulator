#pragma once
#ifndef BOUNTIVE_ASSETSHADER_H_
#define BOUNTIVE_ASSETSHADER_H_

#include "Asset.h"
#include "FileLocation.h"

namespace Bountive
{
	class FileReader;
	class Logger;

	class AssetShader : public Asset
	{
	public:
		enum class ShaderType : GLint
		{
			VERTEX,
			FRAGMENT
		};

		AssetShader(const std::wstring ASSET_ID, const ShaderType& SHADER_TYPE, FileLocation* shaderPath);
		~AssetShader();

		GLboolean load();
		void unload();

		void compile();

		const ShaderType& getShaderType() const;
		const FileLocation& getShaderPath() const;
		const GLint& getGLShaderId() const;

	private:
		static const GLint SIZE;
		static const GLint ERROR_LOG_SIZE;
		static Logger logger;
		
		const ShaderType& mSHADER_TYPE;
		FileLocation* mShaderPath;
		FileReader* mFileReader;
		std::string mShaderCode;
		GLint mShaderId;

		void extractFromFile();
	};
}

#endif