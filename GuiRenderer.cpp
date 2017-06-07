//#include "GuiRenderer.h"
//#include "RenderManager.h"
//#include "ResourceShaderProgram.h"
//#include "MeshList.h"
//#include "Camera.h"
//#include "Logger.h"
//
//namespace Bountive
//{
//	Logger GuiRenderer::logger = Logger("GuiRenderer", Logger::Level::LEVEL_ALL);
//
//	GuiRenderer::GuiRenderer(RenderManager& renderManager) :
//		Renderer(renderManager)
//	{
//		logger.log(Logger::Level::LEVEL_DEBUG, "Creating GuiRenderer...");
//	}
//
//
//	GuiRenderer::~GuiRenderer()
//	{
//		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting GuiRenderer...");
//	}
//
//
//	void GuiRenderer::render(const GLdouble& DELTA_TIME, const std::vector<EntityGui*>& GUI_LIST, const ResourceShaderProgram& activeShaderProgram)
//	{
//		ResourceMesh* guiModel = *MeshList::mGuiMesh;
//
//		activeShaderProgram.use();
//
//		activeShaderProgram.loadMat4("viewMatrixUniform", GL_FALSE, mRenderManager.getCamera().getViewMatrixPtr());
//		activeShaderProgram.loadMat4("projectionMatrixUniform", GL_FALSE, mRenderManager.getCamera().getPerspectiveMatrixPtr());
//
//		guiModel->getVertexArray()->bind();
//
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glDisable(GL_DEPTH_TEST);
//
//		for (GLuint i = 0; i < GUI_LIST.size(); ++i)
//		{
//			glActiveTexture(GL_TEXTURE0);
//			GUI_LIST.at(i)->getTextureWrapper().bind();
//			activeShaderProgram.loadInt1("texture0", 0);
//			activeShaderProgram.loadMat4("transformUniform", GL_FALSE, GUI_LIST.at(i)->getTransform()->getTransformationMatrixPtr());
//			glDrawElements(GL_TRIANGLES, guiModel->getElementBufferData()->getIndiceCount(), GL_UNSIGNED_INT, 0);
//			GUI_LIST.at(i)->getTextureWrapper().unbind();
//		}
//
//		glEnable(GL_DEPTH_TEST);
//		glDisable(GL_BLEND);
//		(*MeshList::mGuiMesh)->getVertexArray()->unbind();
//	}
//}