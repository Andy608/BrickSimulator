#pragma once
#ifndef BOUNTIVE_RESOURCEMESH_H_
#define BOUNTIVE_RESOURCEMESH_H_

#include <glew.h>
#include <vector>
#include "Resource.h"
#include "FileLocation.h"
#include "VertexArrayWrapper.h"
#include "VertexBufferWrapper.h"
#include "ElementBufferWrapper.h"
#include "IRenderable.h"

namespace Bountive
{
	class FileReader;
	class Logger;

	class ResourceMesh : public Resource, public IRenderable
	{
	public:
		ResourceMesh(const std::string RESOURCE_ID, const FileLocation& MESH_FILE_LOCATION);
		virtual ~ResourceMesh();

		virtual void load();
		virtual void unload();

		VertexArrayWrapper* const getVertexArray() const;
		VertexBufferWrapper* const getVertexBufferWrapper(const VertexBufferWrapper::BufferType& BUFFER_TYPE) const;
		ElementBufferWrapper* const getElementBufferData() const;

		virtual void render(const GLdouble& DELTA_TIME);

	private:
		static const char SPACE_DELIMITER;
		static const char SLASH_DELIMITER;

		static FileReader fileReader;
		static Logger logger;

		const FileLocation& mMESH_FILE_LOCATION;

		VertexArrayWrapper* mVertexArray;
		std::vector<VertexBufferWrapper*>* mVertexBufferList;
		ElementBufferWrapper* mElementBufferData;

		void prepareMesh();

		void setElementBuffer(ElementBufferWrapper* wrapper);
		void addBufferData(VertexBufferWrapper* bufferData);

		void addFloatsFromString(std::string line, std::vector<GLfloat>& data, GLuint begin, GLuint amountOfFloats, const char DELIMITER);
		void getIntsFromString(std::string line, std::vector<GLint>& data, GLuint begin, GLuint amountOfInts, const char DELIMITER);
		
		void clearBufferData();
	};
}

#endif