#include "ElementBufferWrapper.h"

namespace Bountive
{
	ElementBufferWrapper::ElementBufferWrapper(std::vector<GLint> indices) :
		mIndiceList(indices)
	{
		createId();
	}


	ElementBufferWrapper::~ElementBufferWrapper()
	{
		glDeleteBuffers(SIZE, &mId);
		mIndiceList.clear();
	}


	void ElementBufferWrapper::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * mIndiceList.size(), &mIndiceList[0], GL_STATIC_DRAW);
	}


	void ElementBufferWrapper::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	const GLuint ElementBufferWrapper::getIndiceCount() const
	{
		return mIndiceList.size();
	}


	const std::vector<GLint> ElementBufferWrapper::getIndices() const
	{
		return mIndiceList;
	}


	void ElementBufferWrapper::createId()
	{
		glGenBuffers(SIZE, &mId);
	}
}