#pragma once
#ifndef BOUNTIVE_ENTITYGUI_H_
#define BOUNTIVE_ENTITYGUI_H_

#include "Entity.h"
#include "AssetMesh.h"
#include "TextureWrapper.h"

namespace Bountive
{
	class AssetMeshGui;
	class Logger;

	class EntityGui : public Entity
	{
	public:
		EntityGui(const std::wstring ASSET_ID, AssetMeshGui& assetMesh, TextureWrapper* guiTextureWrapper);
		~EntityGui();

		virtual void update(const GLdouble& DELTA_TIME);
		virtual void render(const GLdouble& DELTA_TIME);

		const TextureWrapper& getTextureWrapper() const;

	private:
		static Logger logger;

		TextureWrapper* mGuiTextureWrapper;
	};
}

#endif