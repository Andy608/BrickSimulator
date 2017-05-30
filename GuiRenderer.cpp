#include "GuiRenderer.h"
#include "GuiEntities.h"
#include "EntityRegistry.h"
#include "Logger.h"

namespace Bountive
{
	Logger GuiRenderer::logger = Logger("GuiRenderer", Logger::Level::LEVEL_ALL);

	GuiRenderer::GuiRenderer(const ResourceTracker& RESOURCE_TRACKER, const SceneManager& SCENE_MANAGER) :
		Renderer(RESOURCE_TRACKER, SCENE_MANAGER),
		mEntityRegistry(new EntityRegistry())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating GuiRenderer...");
		GuiEntities::initGuis(mRESOURCE_TRACKER, *mEntityRegistry);
	}


	GuiRenderer::~GuiRenderer()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting GuiRenderer...");
		delete mEntityRegistry;
	}


	void GuiRenderer::update(const GLdouble& DELTA_TIME)
	{
		for (GLuint i = 0; i < mEntitiesList->size(); ++i)
		{
			mEntitiesList->at(i)->update(DELTA_TIME);
		}
	}


	void GuiRenderer::render(const GLdouble& DELTA_TIME)
	{
		for (GLuint i = 0; i < mEntitiesList->size(); ++i)
		{
			mEntitiesList->at(i)->render(DELTA_TIME);
		}
	}


	void GuiRenderer::addGui(EntityGui* entity)
	{
		mEntitiesList->push_back(entity);
	}


	void GuiRenderer::removeGui(std::wstring entityId)
	{

	}
}