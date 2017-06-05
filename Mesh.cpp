#include "Mesh.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceMesh::logger = Logger("ResourceMesh", Logger::Level::LEVEL_ALL);

	ResourceMesh::ResourceMesh(const std::string RESOURCE_ID, std::vector<Vertex*> vertices, std::vector<GLuint> indices, std::vector<TextureWrapper*> textures) :
		Resource(RESOURCE_ID),
		mVertices(vertices),
		mIndices(indices),
		mTextures(textures)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceMesh...");
	}


	ResourceMesh::~ResourceMesh()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceMesh...");

		if (mIsLoaded)
		{
			unload();
		}
	}


	void ResourceMesh::load()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTextureCoords));

		glBindVertexArray(0);
	}


	void ResourceMesh::unload()
	{
		for (GLuint i = 0; i < mVertices.size(); ++i)
		{
			if (mVertices.at(i) != nullptr)
			{
				delete mVertices.at(i);
			}
		}

		for (GLuint i = 0; i < mTextures.size(); ++i)
		{
			if (mTextures.at(i) != nullptr)
			{
				delete mTextures.at(i);
			}
		}

		mVertices.clear();
		mIndices.clear();
		mTextures.clear();

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}


	void ResourceMesh::render(const GLdouble& DELTA_TIME, const ResourceShaderProgram& activeShaderProgram)
	{
		GLuint diffuseCount = 0;
		GLuint specularCount = 0;

		for (GLuint i = 0; i < mTextures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			const ResourceTexture::MaterialType& MATERIAL = mTextures.at(i)->getResourceTexture()->getMaterial();

			if (MATERIAL == ResourceTexture::MaterialType::DIFFUSE)
			{
				activeShaderProgram.loadInt1("material.texture_diffuse" + std::to_string(diffuseCount), i);
				++diffuseCount;
			}
			else if (MATERIAL == ResourceTexture::MaterialType::SPECULAR)
			{
				activeShaderProgram.loadInt1("material.texture_specular" + std::to_string(specularCount), i);
				++specularCount;
			}

			glBindTexture(GL_TEXTURE_2D, mTextures.at(i)->getId());
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		/*for (GLuint i = 0; i < mVertices.size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "Rendering mesh!! " + std::to_string(mVertices.at(i)->mPosition.x));
		}*/


		glActiveTexture(GL_TEXTURE0);
	}
}