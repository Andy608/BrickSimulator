#pragma once
#ifndef BOUNTIVE_SCENE_H_
#define BOUNTIVE_SCENE_H_

#include <glew.h>
#include <string>
//#include "EntityGui.h"
#include "Entity.h"
#include "IUpdatable.h"
#include "IRenderable.h"

namespace Bountive
{
	class RenderManager;
	class Logger;

	class Scene : public IUpdatable, public IRenderable
	{
	public:
		const GLint mID;

		Scene(GLint id, std::string name, RenderManager& renderManager);
		virtual ~Scene();

		virtual void showScene() = 0;
		virtual void hideScene() = 0;

		virtual void render(const GLdouble& DELTA_TIME);

		const std::string& getName() const;

	protected:
		static Logger logger;

		const std::string mNAME;
		RenderManager& mRenderManager;

		//std::vector<EntityGui*>* mGuiList;
		std::vector<Entity*>* mEntityList;

		void clearGuiList();
		void clearEntityList();
	};
}

#endif