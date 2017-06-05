#pragma once
#ifndef BOUNTIVE_RESOURCEMESH_H_
#define BOUNTIVE_RESOURCEMESH_H_

#include <vector>
#include "Vertex.h"
#include "Resource.h"
#include "TextureWrapper.h"
#include "ResourceShaderProgram.h"

namespace Bountive
{
	class Logger;

	class ResourceMesh : public Resource
	{
	public:
		ResourceMesh(const std::string RESOURCE_ID, std::vector<Vertex*> vertices, std::vector<GLuint> indices, std::vector<TextureWrapper*> textures);
		virtual ~ResourceMesh();

		virtual void load();
		virtual void unload();

		void render(const GLdouble& DELTA_TIME, const ResourceShaderProgram& activeShaderProgram);

	private:
		static Logger logger;

		std::vector<Vertex*> mVertices;
		std::vector<GLuint> mIndices;
		std::vector<TextureWrapper*> mTextures;

		GLuint VAO, VBO, EBO;
	};
}

#endif