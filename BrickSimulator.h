#pragma once
#ifndef BOUNTIVE_BRICKSIMULATOR_H_
#define BOUNTIVE_BRICKSIMULATOR_H_

#include "FileUtil.h"
#include "Window.h"

namespace Bountive
{
	class BrickSimulator
	{
	public:
		BrickSimulator();
		~BrickSimulator();

		void start();

	private:
		const static GLint TICKS_PER_SECOND;
		const static GLfloat TIME_SLICE;
		const static GLfloat LAG_CAP;

		GLint mTickCount;
		GLint mFramesPerSecond;

		Window* mWindowHandle;
		const FileUtil* const mFileUtil;

		void loop();
		void update();
		void render();
	};
}

#endif