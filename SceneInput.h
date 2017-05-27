#pragma once
#ifndef BOUNTIVE_SCENEINPUT_H_
#define BOUNTIVE_SCENEINPUT_H_

#include <glew.h>
#include "IUpdatable.h"

namespace Bountive
{
	class SceneInput : public IUpdatable
	{
	public:
		SceneInput();
		virtual ~SceneInput();
	};
}

#endif