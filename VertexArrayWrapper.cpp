#include "VertexArrayWrapper.h"
#include "VertexBufferWrapper.h"

namespace Bountive
{
	VertexArrayWrapper::VertexArrayWrapper()
	{
		createId();
	}


	VertexArrayWrapper::~VertexArrayWrapper()
	{
		glDeleteVertexArrays(SIZE, &mId);
	}


	void VertexArrayWrapper::bind() const
	{
		glBindVertexArray(mId);
	}


	void VertexArrayWrapper::unbind() const
	{
		glBindVertexArray(0);
	}


	void VertexArrayWrapper::bindVBOToVAO(GLint bufferIndex, VertexBufferWrapper* bufferData)
	{
		glVertexAttribPointer(bufferIndex, bufferData->getElementsPerVertex(), GL_FLOAT, GL_FALSE, sizeof(GLfloat) * bufferData->getElementsPerVertex(), (GLvoid*)0);
		glEnableVertexAttribArray(bufferIndex);
	}


	void VertexArrayWrapper::createId()
	{
		glGenVertexArrays(SIZE, &mId);
	}
}
