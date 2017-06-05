#pragma once
#ifndef BOUNTIVE_RESOURCEMODEL_H_
#define BOUNTIVE_RESOURCEMODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Resource.h"
#include "Mesh.h"
#include "ResourceShaderProgram.h"

namespace Bountive
{
	class Logger;

	class ResourceModel : public Resource
	{
	public:
		ResourceModel(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME);
		virtual ~ResourceModel();

		virtual void load();
		virtual void unload();
		
		void render(const GLdouble& DELTA_TIME, const ResourceShaderProgram& activeShaderProgram);

	private:
		static Logger logger;

		const FileLocation mFILE_LOCATION;
		std::vector<TextureWrapper*> mLoadedTextures;
		std::vector<ResourceMesh*> mMeshes;

		void processNode(aiNode* node, const aiScene* scene);
		ResourceMesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureWrapper*> loadMaterialTextures(aiMaterial* material, aiTextureType type, const ResourceTexture::MaterialType& MATERIAL);
		TextureWrapper* loadTextureFromModel(std::string textureName, const ResourceTexture::MaterialType& MATERIAL);
	};
}

#endif