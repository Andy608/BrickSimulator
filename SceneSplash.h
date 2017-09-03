#pragma once
#ifndef BOUNTIVE_SCENESPLASH_H_
#define BOUNTIVE_SCENESPLASH_H_

#include "Scene.h"
#include "EntityBarrel.h"
#include "FreeRoamCamera.h"

namespace Bountive
{
	class SplashSceneInput;
	class Logger;

	class SplashScene : public Scene
	{
	public:
		static const std::string NAME;

		SplashScene(GLint id, Window& window, RenderManager& renderManager);
		~SplashScene();

		virtual void showScene();
		virtual void hideScene();

		virtual void update(const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
		SplashSceneInput* mInputHandler;

		FreeRoamCamera* mCamera;
		//EntityGui* bountiveLogo;
		EntityBarrel* mBarrel;
	};
}

#endif