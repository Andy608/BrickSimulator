#include "MeshGui.h"
#include "Logger.h"

namespace Bountive
{
	Logger MeshGui::logger = Logger("MeshGui", Logger::Level::LEVEL_ALL);
	const GLint MeshGui::POSITION_ATTRIBS = 3;
	const GLint MeshGui::COLOR_ATTRIBS = 3;
	const GLint MeshGui::TEXTURE_COORD_ATTRIBS = 2;

	MeshGui::MeshGui(const std::string mRESOURCE_ID) :
		ResourceMesh(mRESOURCE_ID),
		mIndices(std::vector<GLint>() = {
			0, 1, 3, 1, 2, 3
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


	MeshGui::~MeshGui()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting AssetMeshGui...");
	}
}