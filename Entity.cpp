#include "Entity.h"

namespace Bountive
{
	Entity::Entity(std::string entityId, const ResourceMesh& MODEL) :
		mEntityId(entityId), 
		mMODEL(MODEL),
		mPosition(glm::vec3()),
		mRotation(glm::vec3()),
		mScale(glm::vec3())
	{

	}


	Entity::~Entity()
	{
		
	}


	const std::string& Entity::getEntityId() const
	{
		return mEntityId;
	}
}