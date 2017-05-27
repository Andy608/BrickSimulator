#include "AssetMeshGui.h"
#include "Logger.h"

namespace Bountive
{
	Logger AssetMeshGui::logger = Logger("AssetMeshGui", Logger::Level::LEVEL_ALL);
	const GLint AssetMeshGui::POSITION_ATTRIBS = 3;
	const GLint AssetMeshGui::COLOR_ATTRIBS = 3;
	const GLint AssetMeshGui::TEXTURE_COORD_ATTRIBS = 2;

	AssetMeshGui::AssetMeshGui() :
		AssetMesh(L"mesh_gui"),
		mIndices(std::vector<GLint>() = { 
			0, 1, 3, 
			1, 2, 3 
		}),
		mPositions(std::vector<GLfloat>() = { 
			 0.5f,  0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		}),
		mColors(std::vector<GLfloat>() = { 
			1.0, 1.0, 1.0, 
			1.0, 1.0, 1.0, 
			1.0, 1.0, 1.0, 
			1.0, 1.0, 1.0 
		}),
		mTextureCoords(std::vector<GLfloat>() = 
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		})

	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating AssetMeshGui...");

		addVertexBuffer(new VertexBufferWrapper(mPositions, POSITION_ATTRIBS));
		addVertexBuffer(new VertexBufferWrapper(mColors, COLOR_ATTRIBS));
		addVertexBuffer(new VertexBufferWrapper(mTextureCoords, TEXTURE_COORD_ATTRIBS));
		setElementBuffer(new ElementBufferWrapper(mIndices));
		prepareMesh();
	}


	AssetMeshGui::~AssetMeshGui()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetMeshGui...");
		unload();
	}


	GLboolean AssetMeshGui::load()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, L"Successfully loaded AssetMeshGui: " + mASSET_ID);
		mIsLoaded = GL_TRUE;
		return mIsLoaded;
	}


	void AssetMeshGui::unload()
	{

	}
}