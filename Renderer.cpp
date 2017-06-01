#include "Renderer.h"
#include "RenderManager.h"
#include "Logger.h"

namespace Bountive
{
	Logger Renderer::logger = Logger("Renderer", Logger::Level::LEVEL_ALL);

	Renderer::Renderer(RenderManager& renderManager) :
		mRenderManager(renderManager)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating Renderer...");
	}


	Renderer::~Renderer()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting Renderer...");
	}
}