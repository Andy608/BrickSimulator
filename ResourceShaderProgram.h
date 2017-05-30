#pragma once
#ifndef BOUNTIVE_RESOURCESHADERPROGRAM_H_
#define BOUNTIVE_RESOURCESHADERPROGRAM_H_

#include <vector>
#include "ResourceShader.h"

namespace Bountive
{
	class FileLocation;
	class Logger;

	class ResourceShaderProgram : public Resource
	{
	public:
		ResourceShaderProgram(const std::string RESOURCE_ID);
		~ResourceShaderProgram();

		virtual GLboolean load();
		virtual void unload();

		void use() const;

		void attachShader(ResourceShader* shader);
		void compileProgram();

		const GLint& getProgramId() const;

	private:
		static const GLint ERROR_LOG_SIZE;
		static Logger logger;

		GLint mProgramId;
		std::vector<ResourceShader*> mActiveShaders;
	};
}

#endif