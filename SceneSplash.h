#pragma once
#ifndef BOUNTIVE_SCENESPLASH_H_
#define BOUNTIVE_SCENESPLASH_H_

#include "Scene.h"

namespace Bountive
{
	class Window;
	class SplashSceneInput;
	class Logger;

	class SplashScene : public Scene
	{
	public:
		static const std::string NAME;

		SplashScene(const Window& WINDOW_HANDLE, GLint id);
		~SplashScene();

		virtual void update(const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
		SplashSceneInput* mInputHandler;
	};
}

#endif