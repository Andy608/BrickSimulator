#pragma once 
#ifndef BOUNTIVE_HOMESCENEINPUT_H_
#define BOUNTIVE_HOMESCENEINPUT_H_

#include <glew.h>
#include "InputTracker.h"

namespace Bountive
{
	class Window;
	class Logger;

	class HomeSceneInput
	{
	public:
		HomeSceneInput(const InputTracker& INPUT_TRACKER);
		~HomeSceneInput();

		void update(const Window& window, const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
		const InputTracker& mINPUT_TRACKER;
	};
}

#endif