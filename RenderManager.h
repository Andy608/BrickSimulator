#pragma once
#ifndef BOUNTIVE_RENDERMANAGER_H_
#define BOUNTIVE_RENDERMANAGER_H_

#include <glew.h>
#include "ResourceBundleTracker.h"
#include "GuiRenderer.h"
#include "ModelRenderer.h"

namespace Bountive
{
	class Camera;
	class Logger;

	class RenderManager
	{
	public:
		enum class ShaderProgramType
		{
			GUI_SHADER
		};

		static void updateRenderScreenSize(GLint width, GLint height);

		RenderManager();
		~RenderManager();

		void setShader(ResourceShaderProgram* shader);

		const ResourceShaderProgram& getActiveShader() const;
		GuiRenderer& getGuiRenderer() const;
		ModelRenderer& getModelRenderer() const;
		Camera& getCamera() const;

	private:
		static Logger logger;
		static GLint renderScreenWidth;
		static GLint renderScreenHeight;

		Camera* mCamera;

		ResourceShaderProgram* mActiveShaderProgram;
		GuiRenderer* mGuiRenderer;
		ModelRenderer* mModelRenderer;
	};
}

#endif