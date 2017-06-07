#pragma once
#ifndef BOUNTIVE_ENTITY_H_
#define BOUNTIVE_ENTITY_H_

#include <string>
#include "Transform.h"
#include "IUpdatable.h"
#include "IRenderable.h"
#include "ResourceModel.h"

namespace Bountive
{
	class Entity
	{
	public:
		Entity(std::string ENTITY_ID, ResourceModel& model);
		virtual ~Entity();

		Transform* getTransform() const;
		ResourceModel* getModel() const;

		GLboolean operator==(const Entity& comparison) const;
		
	protected:
		const std::string mENTITY_ID;
		ResourceModel* mModel;
		Transform* mTransform;
	};
}

#endif