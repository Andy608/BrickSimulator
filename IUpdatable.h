#pragma once
#ifndef BOUNTIVE_IUPDATABLE_H_
#define BOUNTIVE_IUPDATABLE_H_

#include <glew.h>

namespace Bountive
{
	class IUpdatable
	{
	public:
		virtual void update(const GLdouble& DELTA_TIME) = 0;
	};
}

#endif