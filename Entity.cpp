#include "Entity.h"

namespace Bountive
{
	Entity::Entity(std::string ENTITY_ID, const ResourceMesh& MODEL) :
		mENTITY_ID(ENTITY_ID),
		mMODEL(MODEL),
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