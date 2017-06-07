#include "VertexBufferWrapper.h"
#include <gl\GL.h>

namespace Bountive
{
	VertexBufferWrapper::VertexBufferWrapper(const BufferType& BUFFER_TYPE, std::vector<GLfloat> buffer, GLint elementsPerVertex) :
		GLWrapper(),
		mBUFFER_TYPE(BUFFER_TYPE),
		mBufferData(buffer),
		mElementsPerVertex(elementsPerVertex),
		mVertexCount(mBufferData.size() / mElementsPerVertex)
	{
		createId();
	}


	VertexBufferWrapper::~VertexBufferWrapper()
	{
		glDeleteBuffers(SIZE, &mId);
		mBufferData.clear();
	}


	void VertexBufferWrapper::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mBufferData.size(), &mBufferData[0], GL_STATIC_DRAW);
	}


	void VertexBufferWrapper::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	const GLuint& VertexBufferWrapper::getElementsPerVertex() const
	{
		return mElementsPerVertex;
	}


	const GLuint& VertexBufferWrapper::getVertexCount() const
	{
		return mVertexCount;
	}


	const std::vector<GLfloat> VertexBufferWrapper::getBufferData() const
	{
		return mBufferData;
	}


	void VertexBufferWrapper::createId()
	{
		glGenBuffers(SIZE, &mId);
	}
}