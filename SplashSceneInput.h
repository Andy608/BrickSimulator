#pragma once
#ifndef BOUNTIVE_SPLASHSCENEINPUT_H_
#define BOUNTIVE_SPLASHSCENEINPUT_H_

#include "SceneInput.h"

namespace Bountive
{
	class Logger;

	class SplashSceneInput : public SceneInput
	{
	public:
		SplashSceneInput();
		~SplashSceneInput();

		virtual void update(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
	};
}

#endif