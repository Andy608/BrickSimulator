#include "Entity.h"

namespace Bountive
{
	Entity::Entity(std::string ENTITY_ID, ResourceModel& model) :
		mENTITY_ID(ENTITY_ID),
		mModel(&model),
		mTransform(new Transform())
	{

	}


	Entity::~Entity()
	{
		delete mTransform;
	}


	Transform* Entity::getTransform() const
	{
		return mTransform;
	}


	ResourceModel* Entity::getModel() const
	{
		return mModel;
	}


	GLboolean Entity::operator==(const Entity& comparison) const
	{
		if (mENTITY_ID == comparison.mENTITY_ID)
		{
			return GL_TRUE;
		}
		else
		{
			return GL_FALSE;
		}
	}
}