#include "BrickSimulator.h"
#include "EntityGui.h"
#include "AssetMeshGui.h"
#include "Logger.h"

namespace Bountive
{
	Logger EntityGui::logger = Logger("EntityGui", Logger::Level::LEVEL_ALL);

	EntityGui::EntityGui(const std::wstring ASSET_ID, AssetMeshGui& assetMesh, TextureWrapper* guiTextureWrapper) :
		Entity(ASSET_ID, assetMesh),
		mGuiTextureWrapper(guiTextureWrapper)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating EntityGui...");

		mGuiTextureWrapper->generateGLtexture();
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
		logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mMODEL.getElementBufferData()->getIndiceCount()));
		mMODEL.getVertexArray()->bind();
		glDrawElements(GL_TRIANGLES, mMODEL.getElementBufferData()->getIndiceCount(), GL_UNSIGNED_INT, 0);
		mMODEL.getVertexArray()->unbind();
	}


	const TextureWrapper& EntityGui::getTextureWrapper() const
	{
		return *mGuiTextureWrapper;
	}
}