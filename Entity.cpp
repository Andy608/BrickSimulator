#include "Entity.h"

namespace Bountive
{
	Entity::Entity(std::wstring entityId, const AssetMesh& MODEL) :
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


	const std::wstring& Entity::getEntityId() const
	{
		return mEntityId;
	}
}