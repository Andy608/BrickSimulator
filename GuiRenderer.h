#pragma once
#ifndef BOUNTIVE_GUIRENDERER_H_
#define BOUNTIVE_GUIRENDERER_H_

#include "Renderer.h"
#include "EntityGui.h"

namespace Bountive
{
	class Logger;
	class EntityRegistry;

	class GuiRenderer : public Renderer
	{
	public:
		GuiRenderer(const AssetManager& ASSET_MANAGER, const SceneManager& SCENE_MANAGER);
		~GuiRenderer();

		virtual void update(const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

		void addGui(EntityGui* entity);
		void removeGui(std::wstring entityId);

	private:
		static Logger logger;

		EntityRegistry* mEntityRegistry;
	};
}

#endif