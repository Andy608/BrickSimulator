#pragma once
#ifndef BOUNTIVE_SCENEINPUT_H_
#define BOUNTIVE_SCENEINPUT_H_

#include <glew.h>
#include "InputTracker.h"

namespace Bountive
{
	class Window;

	class SceneInput
	{
	public:
		SceneInput(const InputTracker& INPUT_TRACKER);
		virtual ~SceneInput();

		virtual void update(const Window& window, const GLdouble& DELTA_TIME) = 0;

	protected:
		const InputTracker& mINPUT_TRACKER;
	};
}

#endif