#pragma once
#ifndef BOUNTIVE_VERTEXARRAYWRAPPER_H_
#define BOUNTIVE_VERTEXARRAYWRAPPER_H_

#include "VertexBufferWrapper.h"

namespace Bountive
{
	class VertexArrayWrapper : public GLWrapper
	{
	public:
		VertexArrayWrapper();
		~VertexArrayWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		void bindVBOToVAO(GLint bufferIndex, VertexBufferWrapper* bufferData);

	private:
		virtual void createId();
	};
}

#endif