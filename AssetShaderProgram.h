#pragma once
#ifndef BOUNTIVE_ASSETSHADERPROGRAM_H_
#define BOUNTIVE_ASSETSHADERPROGRAM_H_

#include <vector>
#include "AssetShader.h"

namespace Bountive
{
	class FileLocation;
	class Logger;

	class AssetShaderProgram : public Asset
	{
	public:
		AssetShaderProgram(const std::wstring ASSET_ID);
		~AssetShaderProgram();

		virtual GLboolean load();
		virtual void unload();

		void use() const;

		void attachShader(AssetShader* shader);
		void compileProgram();

		const GLint& getProgramId() const;

	private:
		static const GLint ERROR_LOG_SIZE;
		static Logger logger;

		GLint mProgramId;
		std::vector<AssetShader*> mActiveShaders;
	};
}

#endif