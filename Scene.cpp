#include "Scene.h"

namespace Bountive
{
	Scene::Scene(const Window& WINDOW_HANDLE, GLint id, std::string name) :
		mWINDOW_HANDLE(WINDOW_HANDLE),
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