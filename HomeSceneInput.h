#pragma once 
#ifndef BOUNTIVE_HOMESCENEINPUT_H_
#define BOUNTIVE_HOMESCENEINPUT_H_

#include <glew.h>
#include "SceneInput.h"

namespace Bountive
{
	class Logger;

	class HomeSceneInput : public SceneInput
	{
	public:
		HomeSceneInput();
		~HomeSceneInput();

		virtual void update(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
	};
}

#endif