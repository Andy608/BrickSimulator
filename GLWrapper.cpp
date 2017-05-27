#include "GLWrapper.h"

namespace Bountive
{
	const GLuint GLWrapper::SIZE = 1;

	GLWrapper::GLWrapper()
	{
		
	}


	GLWrapper::~GLWrapper()
	{

	}


	const GLuint& GLWrapper::getId() const
	{
		return mId;
	}
}