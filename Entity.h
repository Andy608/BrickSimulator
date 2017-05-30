#pragma once
#ifndef BOUNTIVE_ENTITY_H_
#define BOUNTIVE_ENTITY_H_

#include <string>
#include <glew.h>
#include <glm\vec3.hpp>
#include "IUpdatable.h"
#include "IRenderable.h"
#include "ResourceMesh.h"

namespace Bountive
{
	class Entity : public IUpdatable, public IRenderable
	{
	public:
		Entity(std::string entityId, const ResourceMesh& MODEL);
		virtual ~Entity();

		const std::string& getEntityId() const;

	protected:
		std::string mEntityId;
		const ResourceMesh& mMODEL;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;
	};
}

#endif