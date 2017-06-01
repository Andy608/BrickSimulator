#pragma once
#ifndef BOUNTIVE_RESOURCEMESH_H_
#define BOUNTIVE_RESOURCEMESH_H_

#include <glew.h>
#include <vector>
#include "Resource.h"
#include "VertexArrayWrapper.h"
#include "VertexBufferWrapper.h"
#include "ElementBufferWrapper.h"

namespace Bountive
{
	class Logger;

	class ResourceMesh : public Resource
	{
	public:
		ResourceMesh(const std::string RESOURCE_ID);
		virtual ~ResourceMesh();

		virtual void load();
		virtual void unload();

		void addVertexBuffer(VertexBufferWrapper* wrapper);
		void setElementBuffer(ElementBufferWrapper* wrapper);
		
		void prepareMesh();

		VertexArrayWrapper* const getVertexArray() const;
		VertexBufferWrapper* const getVertexBufferList(GLint bufferIndex) const;
		ElementBufferWrapper* const getElementBufferData() const;

	private:
		static Logger logger;

		VertexArrayWrapper* mVertexArray;
		std::vector<VertexBufferWrapper*>* mVertexBufferList;
		ElementBufferWrapper* mElementBufferData;

		void addBufferData(VertexBufferWrapper* bufferData);
		void clearBufferData();
	};
}

#endif