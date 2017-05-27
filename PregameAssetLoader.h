#pragma once
#ifndef BOUNTIVE_PREGAMEASSETLOADER_H_
#define BOUNTIVE_PREGAMEASSETLOADER_H_

#include "AssetLoader.h"
#include "AssetImage.h"
#include "AssetMesh.h"
#include "AssetShader.h"
#include "AssetShaderProgram.h"

namespace Bountive
{
	class Logger;

	class PregameAssetLoader : public AssetLoader
	{
	public:
		AssetImage* mBountiveLogo;

		AssetMesh* mGuiMesh;

		AssetShader* mGuiVertexShader;
		AssetShader* mGuiFragmentShader;
		AssetShaderProgram* mGuiShaderProgram;

		PregameAssetLoader();
		~PregameAssetLoader();

		virtual void initAssets();
			
	private:
		static Logger logger;

		void loadShaders();
};

}

#endif