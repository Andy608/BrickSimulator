#pragma once
#ifndef BOUNTIVE_ENTITY_H_
#define BOUNTIVE_ENTITY_H_

#include <string>
#include <glew.h>
#include <glm\vec3.hpp>
#include "IUpdatable.h"
#include "IRenderable.h"
#include "AssetMesh.h"

namespace Bountive
{
	class Entity : public IUpdatable, public IRenderable
	{
	public:
		Entity(std::wstring entityId, const AssetMesh& MODEL);
		virtual ~Entity();

		const std::wstring& getEntityId() const;

	protected:
		std::wstring mEntityId;
		const AssetMesh& mMODEL;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;
	};
}

#endif