#pragma once
#ifndef BOUNTIVE_IRENDERABLE_H_
#define BOUNTIVE_IRENDERABLE_H_

#include <glew.h>

namespace Bountive
{
	class IRenderable
	{
	public:
		virtual void render(const GLdouble& DELTA_TIME) = 0;
	};
}

#endif