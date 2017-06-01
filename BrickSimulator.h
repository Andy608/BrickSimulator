#pragma once
#ifndef BOUNTIVE_BRICKSIMULATOR_H_
#define BOUNTIVE_BRICKSIMULATOR_H_

#include "DirectoryUtil.h"
#include "Window.h"
#include "GameSettingsHandler.h"
#include "ResourceBundleTracker.h"
#include "EntityTracker.h"
#include "TextureList.h"

namespace Bountive
{
	class Logger;
	class LoggerUtil;

	class BrickSimulator
	{
	public:
		static BrickSimulator* instance;

		static BrickSimulator* init();

		~BrickSimulator();

		void start();
		void saveSettings() const;

		Window* getWindow() const;
		SceneManager* getSceneManager() const;
		InputTracker* getInputTracker() const;

	private:
		static Logger logger;
		static const GLint TICKS_PER_SECOND;
		static const GLfloat TIME_SLICE;
		static const GLfloat LAG_CAP;

		GLint mTickCount;
		GLint mFramesPerSecond;

		const DirectoryUtil* const mDIRECTORY_UTIL;
		const LoggerUtil* const mLOGGER_UTIL;

		Window* const mWindow;
		GameSettingsHandler* const mGameSettingsHandler;

		ResourceBundleTracker* mResourceBundleTracker;
		TextureList* mTextureList;

		EntityTracker* mEntityTracker;
		SceneManager* mSceneManager;
		RenderManager* mRenderManager;
		InputTracker* mInputTracker;

		BrickSimulator();

		void loop();
		void update(const GLdouble& DELTA_TIME);
		void render(const GLdouble& DELTA_TIME);
	};
}

#endif