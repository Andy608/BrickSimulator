#pragma once
#ifndef BOUNTIVE_STARTUPRESOURCELOADER_H_
#define BOUNTIVE_STARTUPRESOURCELOADER_H_

#include "ResourceLoader.h"
#include "ResourceImage.h"
#include "ResourceMesh.h"
#include "ResourceShader.h"
#include "ResourceShaderProgram.h"

namespace Bountive
{
	class Logger;

	class StartupResourceLoader : public ResourceLoader
	{
	public:
		ResourceImage* mBountiveLogo;

		ResourceMesh* mGuiMesh;

		ResourceShader* mGuiVertexShader;
		ResourceShader* mGuiFragmentShader;
		ResourceShaderProgram* mGuiShaderProgram;

		StartupResourceLoader();
		~StartupResourceLoader();

		virtual void initResources();
			
	private:
		static Logger logger;

		void loadShaders();
};

}

#endif