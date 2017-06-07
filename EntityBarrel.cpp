#include "EntityBarrel.h"
#include "ModelResourceBundle.h"

namespace Bountive
{
	EntityBarrel::EntityBarrel() :
		Entity("entity_barrel", *ModelResourceBundle::mModelBarrel)
	{

	}


	EntityBarrel::~EntityBarrel()
	{

	}
}