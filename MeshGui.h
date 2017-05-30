#pragma once
#ifndef BOUNTIVE_MESHGUI_H_
#define BOUNTIVE_MESHGUI_H_

#include "ResourceMesh.h"

namespace Bountive
{
	class Logger;

	class MeshGui : public ResourceMesh
	{
	public:
		MeshGui(const std::string mRESOURCE_ID);
		~MeshGui();

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