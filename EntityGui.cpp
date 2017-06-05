#include "BrickSimulator.h"
#include "EntityGui.h"
#include "MeshList.h"
#include "Logger.h"

namespace Bountive
{
	Logger EntityGui::logger = Logger("EntityGui", Logger::Level::LEVEL_ALL);

	EntityGui::EntityGui(const std::string ENTITY_ID, TextureWrapper* guiTextureWrapper) :
		Entity(ENTITY_ID, **MeshList::mGuiMesh),
		mGuiTextureWrapper(guiTextureWrapper)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating EntityGui...");

		mGuiTextureWrapper->generateGLtexture();
		mTransform->setDimensions(mGuiTextureWrapper->getResourceTexture()->getAspectRatio(), 1.0f, 1.0f);
	}


	EntityGui::~EntityGui()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting EntityGui...");
		delete mGuiTextureWrapper;
	}


	void EntityGui::update(const GLdouble& DELTA_TIME)
	{
		
	}


	void EntityGui::render(const GLdouble& DELTA_TIME)
	{

	}


	const TextureWrapper& EntityGui::getTextureWrapper() const
	{
		return *mGuiTextureWrapper;
	}
}