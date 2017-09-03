#pragma once
#ifndef BOUNTIVE_RESOURCESHADER_H_
#define BOUNTIVE_RESOURCESHADER_H_

#include "Resource.h"
#include "FileLocation.h"

namespace Bountive
{
	class FileLocation;
	class FileReader;
	class Logger;

	class ResourceShader : public Resource
	{
	public:
		enum class EnumShaderType : GLint
		{
			VERTEX,
			FRAGMENT
		};

		ResourceShader(const std::string RESOURCE_ID, const EnumShaderType& SHADER_TYPE, FileLocation* shaderPath);
		~ResourceShader();

		virtual void load();
		virtual void unload();

		void compile();

		const EnumShaderType& getShaderType() const;
		const FileLocation& getShaderPath() const;
		const GLint& getGLShaderId() const;

	private:
		static const GLint SIZE;
		static const GLint ERROR_LOG_SIZE;
		static Logger logger;

		const EnumShaderType& mSHADER_TYPE;
		FileLocation* mShaderPath;
		FileReader* mFileReader;
		std::string mShaderCode;
		GLint mShaderId;

		void extractFromFile();
	};
}

#endif