#pragma once
#ifndef BOUNTIVE_RESOURCEMESH2_H_
#define BOUNTIVE_RESOURCEMESH2_H_

#include <glew.h>
#include <vector>
#include "Resource.h"
#include "VertexArrayWrapper.h"
#include "VertexBufferWrapper.h"
#include "ElementBufferWrapper.h"

namespace Bountive
{
	class Logger;

	class ResourceMeshOld : public Resource
	{
	public:
		ResourceMeshOld(const std::string RESOURCE_ID);
		virtual ~ResourceMeshOld();

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