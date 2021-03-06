#pragma once
#ifndef BOUNTIVE_VERTEXBUFFERWRAPPER_H_
#define BOUNTIVE_VERTEXBUFFERWRAPPER_H_

#include "GLWrapper.h"

namespace Bountive
{
	class VertexBufferWrapper : public GLWrapper
	{
	public:
		enum class BufferType : const GLuint
		{
			POSITIONS,
			TEXTURE_COORDS,
			NORMALS
		};

		const BufferType mBUFFER_TYPE;

		VertexBufferWrapper(const BufferType& BUFFER_TYPE, std::vector<GLfloat> buffer, GLint elementsPerVertex);
		~VertexBufferWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		const GLuint& getElementsPerVertex() const;
		const GLuint& getVertexCount() const;
		const std::vector<GLfloat> getBufferData() const;

	private:
		GLuint mElementsPerVertex;
		GLuint mVertexCount;
		std::vector<GLfloat> mBufferData;

		virtual void createId();
	};
}

#endif