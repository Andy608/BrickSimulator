#include "ResourceMeshGui.h"
#include "Logger.h"

namespace Bountive
{
	Logger ResourceMeshGui::logger = Logger("ResourceMeshGui", Logger::Level::LEVEL_ALL);
	const GLint ResourceMeshGui::POSITION_ATTRIBS = 3;
	const GLint ResourceMeshGui::COLOR_ATTRIBS = 3;
	const GLint ResourceMeshGui::TEXTURE_COORD_ATTRIBS = 2;

	ResourceMeshGui::ResourceMeshGui(const std::string mRESOURCE_ID) :
		ResourceMeshOld(mRESOURCE_ID),
		mIndices(std::vector<GLint>() = {
			0, 1, 3, 1, 2, 3
		}),
		mPositions(std::vector<GLfloat>() = { 
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
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
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ResourceMeshGui...");

		addVertexBuffer(new VertexBufferWrapper(mPositions, POSITION_ATTRIBS));
		addVertexBuffer(new VertexBufferWrapper(mColors, COLOR_ATTRIBS));
		addVertexBuffer(new VertexBufferWrapper(mTextureCoords, TEXTURE_COORD_ATTRIBS));
		setElementBuffer(new ElementBufferWrapper(mIndices));
		prepareMesh();
	}


	ResourceMeshGui::~ResourceMeshGui()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ResourceMeshGui...");
	}
}