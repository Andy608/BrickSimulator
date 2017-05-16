#pragma once
#ifndef BOUNTIVE_BRICKSIMULATOR_H_
#define BOUNTIVE_BRICKSIMULATOR_H_

#include <log4cxx/logger.h>
#include "DirectoryUtil.h"
#include "InputHandler.h"
#include "Window.h"
#include "GameSettingsHandler.h"

namespace Bountive
{
	class BrickSimulator
	{
	public:
		static BrickSimulator* instance;
		static BrickSimulator* init();

		~BrickSimulator();

		void start();
		void saveSettings() const;

	private:
		static log4cxx::LoggerPtr brickSimulatorLogger;

		const static GLint TICKS_PER_SECOND;
		const static GLfloat TIME_SLICE;
		const static GLfloat LAG_CAP;

		GLint mTickCount;
		GLint mFramesPerSecond;

		const DirectoryUtil* const mDIRECTORY_UTIL;
		Window* mWindowHandle;
		GameSettingsHandler* const mGameSettingsHandler;
		InputHandler* const mInputHandler;

		BrickSimulator();

		void loop();
		void update();
		void render();
	};
}

#endif