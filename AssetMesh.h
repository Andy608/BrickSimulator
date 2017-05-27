#pragma once
#ifndef BOUNTIVE_ASSETMESH_H_
#define BOUNTIVE_ASSETMESH_H_

#include <glew.h>
#include <vector>
#include "Asset.h"
#include "VertexArrayWrapper.h"
#include "VertexBufferWrapper.h"
#include "ElementBufferWrapper.h"

namespace Bountive
{
	class Logger;

	class AssetMesh : public Asset
	{
	public:
		AssetMesh(const std::wstring ASSET_ID);
		virtual ~AssetMesh();

		virtual GLboolean load() = 0;
		virtual void unload() = 0;

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