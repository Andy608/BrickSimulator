#pragma once
#ifndef BOUNTIVE_ELEMENTBUFFERWRAPPER_H_
#define BOUNTIVE_ELEMENTBUFFERWRAPPER_H_

#include "GLWrapper.h"

namespace Bountive
{
	class ElementBufferWrapper : public GLWrapper
	{
	public:
		ElementBufferWrapper(std::vector<GLint> indices);
		~ElementBufferWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		const GLuint getIndiceCount() const;
		const std::vector<GLint> getIndices() const;

	private:
		std::vector<GLint> mIndiceList;

		virtual void createId();
	};
}

#endif