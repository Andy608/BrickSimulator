#pragma once
#ifndef BOUNTIVE_SPLASHSCENEINPUT_H_
#define BOUNTIVE_SPLASHSCENEINPUT_H_

#include "SceneInput.h"
#include "InputTracker.h"

namespace Bountive
{
	class Window;
	class Logger;

	class SplashSceneInput : public SceneInput
	{
	public:
		SplashSceneInput(const InputTracker& INPUT_TRACKER);
		~SplashSceneInput();

		virtual void update(const Window& window, const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
	};
}

#endif