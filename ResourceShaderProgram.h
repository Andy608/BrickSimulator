#pragma once
#ifndef BOUNTIVE_RESOURCESHADERPROGRAM_H_
#define BOUNTIVE_RESOURCESHADERPROGRAM_H_

#include <vector>
#include "ResourceShader.h"
#include "FileLocation.h"

namespace Bountive
{
	class Logger;

	class ResourceShaderProgram : public Resource
	{
	public:
		ResourceShaderProgram(const std::string RESOURCE_ID);
		~ResourceShaderProgram();

		virtual void load();
		virtual void unload();

		void use() const;

		void attachShader(ResourceShader* shader);

		const GLint& getProgramID() const;

		GLuint getUniformID(std::string uniformName) const;

		void loadInt1(std::string uniformName, GLint integer) const;
		void loadFloat1(std::string uniformName, GLfloat floatingPoint) const;
		void loadMat4(std::string uniformName, GLboolean transpose, const GLfloat* matrixPtr) const;

	private:
		static const GLint ERROR_LOG_SIZE;
		static Logger logger;

		GLint mProgramID;
		std::vector<ResourceShader*> mActiveShaders;

		void compileProgram();
	};
}

#endif