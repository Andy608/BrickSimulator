#pragma once
#ifndef BOUNTIVE_SCENE_H_
#define BOUNTIVE_SCENE_H_

#include <glew.h>
#include <string>
#include "IUpdatable.h"
#include "IRenderable.h"
#include "RenderManager.h"

namespace Bountive
{
	class Scene : public IUpdatable, public IRenderable
	{
	public:
		const GLint mID;

		Scene(GLint id, std::string name);
		virtual ~Scene();

		virtual void showScene() = 0;
		virtual void hideScene() = 0;

		const std::string& getName() const;
		
	protected:
		const std::string mNAME;

		RenderManager& mRenderManager;
	};
}

#endif