#include "BrickSimulator.h"
#include "RenderManager.h"
#include "ShaderList.h"
#include "Scene.h"
#include "Logger.h"

namespace Bountive
{
	Logger Scene::logger = Logger("Scene", Logger::Level::LEVEL_ALL);

	Scene::Scene(GLint id, std::string name, RenderManager& renderManager) :
		mID(id), 
		mNAME(name),
		mRenderManager(renderManager),
		mGuiList(new std::vector<EntityGui*>())
	{

	}


	Scene::~Scene()
	{
		mGuiList->clear();
		delete mGuiList;
	}


	void Scene::render(const GLdouble& DELTA_TIME)
	{
		mRenderManager.setShader(*ShaderList::mGuiShaderProgram);
		mRenderManager.getGuiRenderer().render(DELTA_TIME, *mGuiList, mRenderManager.getActiveShader());
	}


	const std::string& Scene::getName() const
	{
		return mNAME;
	}


	void Scene::clearGuiList()
	{
		for (GLuint i = 0; i < mGuiList->size(); ++i)
		{
			logger.log(Logger::Level::LEVEL_DEBUG, "CLEARING ENTITY LIST");
			if (mGuiList->at(i) != nullptr)
			{
				delete mGuiList->at(i);
			}
		}

		mGuiList->clear();
	}
}