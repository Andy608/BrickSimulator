#include "Scene.h"

namespace Bountive
{
	Scene::Scene(GLint id, std::string name) :
		mID(id), 
		mNAME(name)
	{

	}


	Scene::~Scene()
	{

	}


	const std::string& Scene::getName() const
	{
		return mNAME;
	}
}