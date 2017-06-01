#pragma once
#ifndef BOUNTIVE_RENDERMANAGER_H_
#define BOUNTIVE_RENDERMANAGER_H_

#include <glew.h>
#include "ResourceBundleTracker.h"
#include "GuiRenderer.h"

namespace Bountive
{
	class Logger;

	class RenderManager
	{
	public:
		enum class ShaderProgramType
		{
			GUI_SHADER
		};

		RenderManager();
		~RenderManager();

		void setShader(ResourceShaderProgram* shader);

		GLuint getUniformID(std::string uniformName) const;

		void loadInt1(std::string uniformName, GLint integer) const;
		void loadMat4(std::string uniformName, GLboolean transpose, const GLfloat* matrixPtr) const;

		const ResourceShaderProgram& getActiveShader() const;
		GuiRenderer& getGuiRenderer() const;

	private:
		static Logger logger;

		ResourceShaderProgram* mActiveShaderProgram;
		GuiRenderer* mGuiRenderer;
	};
}

#endif