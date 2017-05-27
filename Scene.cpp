#include "BrickSimulator.h"
#include "Scene.h"

namespace Bountive
{
	Scene::Scene(GLint id, std::string name) :
		mID(id), 
		mNAME(name),
		mRenderManager(*BrickSimulator::instance->getRenderManager())
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