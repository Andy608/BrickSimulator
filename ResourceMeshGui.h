#pragma once
#ifndef BOUNTIVE_RESOURCEMESHGUI_H_
#define BOUNTIVE_RESOURCEMESHGUI_H_

#include "ResourceMesh.h"

namespace Bountive
{
	class Logger;

	class ResourceMeshGui : public ResourceMeshOld
	{
	public:
		ResourceMeshGui(const std::string mRESOURCE_ID);
		~ResourceMeshGui();

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