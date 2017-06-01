#pragma once
#ifndef BOUNTIVE_GUIRESOURCEBUNDLE_H_
#define BOUNTIVE_GUIRESOURCEBUNDLE_H_

#include "ResourceBundle.h"
#include "ResourceTexture.h"
#include "ResourceMeshGui.h"
#include "ResourceShaderProgram.h"

namespace Bountive
{
	class Logger;

	class GuiResourceBundle : public ResourceBundle
	{
	public:
		static ResourceMeshGui* mGuiMesh;
		static ResourceTexture* mBountiveLogoTexture;

		static ResourceShader* mGuiVertexShader;
		static ResourceShader* mGuiFragmentShader;
		static ResourceShaderProgram* mGuiShaderProgram;

		GuiResourceBundle();
		virtual ~GuiResourceBundle();

		virtual void loadResourceBundle();
		virtual void unloadResourceBundle();

	private:
		static Logger logger;
	};
}
#endif