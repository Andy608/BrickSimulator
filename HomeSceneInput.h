#pragma once 
#ifndef BOUNTIVE_HOMESCENEINPUT_H_
#define BOUNTIVE_HOMESCENEINPUT_H_

#include <glew.h>
#include "SceneInput.h"

namespace Bountive
{
	class Window;
	class Logger;

	class HomeSceneInput : public SceneInput
	{
	public:
		HomeSceneInput(const InputTracker& INPUT_TRACKER);
		~HomeSceneInput();

		virtual void update(const Window& window, const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
	};
}

#endif