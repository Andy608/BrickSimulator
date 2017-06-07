#pragma once
#ifndef BOUNTIVE_MODELRESOURCEBUNDLE_H_
#define BOUNTIVE_MODELRESOURCEBUNDLE_H_

#include "ResourceBundle.h"
#include "ResourceShader.h"
#include "ResourceShaderProgram.h"
#include "ModelBarrel.h"

namespace Bountive
{
	class Logger;

	class ModelResourceBundle : public ResourceBundle
	{
	public:
		static ModelBarrel* mModelBarrel;

		static ResourceShader* mModelVertexShader;
		static ResourceShader* mModelFragmentShader;
		static ResourceShaderProgram* mModelShaderProgram;

		ModelResourceBundle();
		virtual ~ModelResourceBundle();

		virtual void loadResourceBundle();
		virtual void unloadResourceBundle();

	private:
		static Logger logger;
	};
}

#endif