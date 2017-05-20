#pragma once
#ifndef BOUNTIVE_HOMESCENE_H_
#define BOUNTIVE_HOMESCENE_H_

#include "Scene.h"

namespace Bountive
{
	class Logger;
	class HomeSceneInput;

	class HomeScene : public Scene
	{
	public:
		static Logger logger;
		static const std::string NAME;

		HomeScene(GLint id);
		~HomeScene();

		virtual void HomeScene::update(const Window& window, const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

	private:
		HomeSceneInput* mInputHandler;
	};
}

#endif