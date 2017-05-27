#pragma once
#ifndef BOUNTIVE_GLWRAPPER_H_
#define BOUNTIVE_GLWRAPPER_H_

#include <glew.h>
#include <vector>

namespace Bountive
{
	class GLWrapper
	{
	public:
		GLWrapper();
		virtual ~GLWrapper();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		const GLuint& getId() const;

	protected:
		static const GLuint SIZE;
		GLuint mId;

		virtual void createId() = 0;
	};
}

#endif