#pragma once
#ifndef BOUNTIVE_SCENEHOME_H_
#define BOUNTIVE_SCENEHOME_H_

#include "Scene.h"

namespace Bountive
{
	class HomeSceneInput;
	class Logger;

	class HomeScene : public Scene
	{
	public:
		static const std::string NAME;

		HomeScene(GLint id);
		~HomeScene();

		virtual void showScene();
		virtual void hideScene();

		virtual void update(const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
		HomeSceneInput* mInputHandler;
	};
}

#endif