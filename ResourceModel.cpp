#include "ResourceModel.h"
#include "StringUtil.h"
#include "DirectoryUtil.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceModel::logger = Logger("ResourceModel", Logger::Level::LEVEL_ALL);

	ResourceModel::ResourceModel(const std::string RESOURCE_ID, const FileDirectory& DIRECTORY, const std::wstring FILE_NAME) :
		Resource(RESOURCE_ID),
		mFILE_LOCATION(FileLocation(&DIRECTORY, FILE_NAME, FileLocation::OBJ_EXTENSION)),
		mMeshes(std::vector<ResourceMesh*>()),
		mLoadedTextures(std::vector<TextureWrapper*>())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceModel!");
	}


	ResourceModel::~ResourceModel()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceModel...");

		if (mIsLoaded)
		{
			unload();
		}
	}


	void ResourceModel::load()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(StringUtil::wtos(mFILE_LOCATION.getFullPath()), aiProcess_Triangulate | aiProcess_FlipUVs);
		
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			logger.log(Logger::Level::LEVEL_ERROR, L"Error loading model from file: " + mFILE_LOCATION.getFullPath());
			return;
		}

		processNode(scene->mRootNode, scene);

		for (GLuint i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes.at(i)->load();
		}
	}


	void ResourceModel::unload()
	{
		for (GLuint i = 0; i < mMeshes.size(); ++i)
		{
			if (mMeshes.at(i) != nullptr)
			{
				delete mMeshes.at(i);
			}
		}
	}


	void ResourceModel::render(const GLdouble& DELTA_TIME, const ResourceShaderProgram& activeShaderProgram)
	{
		for (GLuint i = 0; i < mMeshes.size(); ++i)
		{
			mMeshes.at(i)->render(DELTA_TIME, activeShaderProgram);
		}
	}


	void ResourceModel::processNode(aiNode* node, const aiScene* scene)
	{
		for (GLuint i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mMeshes.push_back(processMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; ++i)
		{
			processNode(node->mChildren[i], scene);
		}
	}


	ResourceMesh* ResourceModel::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex*> vertices;
		std::vector<GLuint> indices;
		std::vector<TextureWrapper*> textures;

		for (GLuint i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex* vertex = new Vertex();
			glm::vec3 vertexData;
			vertexData.x = mesh->mVertices[i].x;
			vertexData.y = mesh->mVertices[i].y;
			vertexData.z = mesh->mVertices[i].z;
			vertex->mPosition = vertexData;

			vertexData.x = mesh->mNormals[i].x;
			vertexData.y = mesh->mNormals[i].y;
			vertexData.z = mesh->mNormals[i].z;
			vertex->mNormal = vertexData;

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vertexData;
				vertexData.x = mesh->mTextureCoords[0][i].x;
				vertexData.y = mesh->mTextureCoords[0][i].y;
				vertex->mTextureCoords = vertexData;
			}
			else
			{
				vertex->mTextureCoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		for (GLuint i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];

			for (GLuint j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			std::vector<TextureWrapper*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, ResourceTexture::MaterialType::DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<TextureWrapper*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, ResourceTexture::MaterialType::SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		logger.log(Logger::Level::LEVEL_DEBUG, "Successfully processed mesh: " + std::string(mesh->mName.C_Str()));
		return new ResourceMesh("MESH ID: " + std::string(mesh->mName.C_Str()), vertices, indices, textures);
	}


	std::vector<TextureWrapper*> ResourceModel::loadMaterialTextures(aiMaterial* material, aiTextureType type, const ResourceTexture::MaterialType& MATERIAL)
	{
		std::vector<TextureWrapper*> textures;

		for (GLuint i = 0; i < material->GetTextureCount(type); ++i)
		{
			aiString str;
			material->GetTexture(type, i, &str);

			bool isTextureLoaded = false;

			for (GLuint j = 0; j < mLoadedTextures.size(); ++j)
			{
				if (mLoadedTextures.at(j)->getResourceTexture()->getResourceId().compare(str.C_Str()) == 0)
				{
					textures.push_back(mLoadedTextures.at(j));
					isTextureLoaded = true;
					break;
				}
			}

			if (!isTextureLoaded)
			{
				textures.push_back(loadTextureFromModel(str.C_Str(), MATERIAL));
			}
		}

		return textures;
	}


	TextureWrapper* ResourceModel::loadTextureFromModel(std::string textureName, const ResourceTexture::MaterialType& MATERIAL)
	{
		ResourceTexture* modelTexture = new ResourceTexture(textureName, *DirectoryUtil::instance->mEXE_IMAGES, StringUtil::stow(textureName), MATERIAL);
		TextureWrapper* textureWrapper = new TextureWrapper(modelTexture);
		return textureWrapper;
	}
}