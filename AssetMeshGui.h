#pragma once
#ifndef BOUNTIVE_ASSETMESHGUI_H_
#define BOUNTIVE_ASSETMESHGUI_H_

#include "AssetMesh.h"

namespace Bountive
{
	class Logger;

	class AssetMeshGui : public AssetMesh
	{
	public:
		AssetMeshGui();
		~AssetMeshGui();

		virtual GLboolean load();
		virtual void unload();

	private:
		static Logger logger;
		static const GLint POSITION_ATTRIBS;
		static const GLint COLOR_ATTRIBS;
		static const GLint TEXTURE_COORD_ATTRIBS;

		std::vector<GLint> mIndices;
		std::vector<GLfloat> mPositions;
		std::vector<GLfloat> mColors;
		std::vector<GLfloat> mTextureCoords;
	};
}

#endif