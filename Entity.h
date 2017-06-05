#pragma once
#ifndef BOUNTIVE_ENTITY_H_
#define BOUNTIVE_ENTITY_H_

#include <string>
#include "Transform.h"
#include "IUpdatable.h"
#include "IRenderable.h"
#include "ResourceMesh.h"

namespace Bountive
{
	class Entity : public IUpdatable, public IRenderable
	{
	public:
		Entity(std::string ENTITY_ID, const ResourceMeshOld& MODEL);
		virtual ~Entity();

		Transform* getTransform() const;

		GLboolean operator==(const Entity& comparison) const;

	protected:
		const std::string mENTITY_ID;
		const ResourceMeshOld& mMODEL;
		Transform* mTransform;
	};
}

#endif