#include "ModelComponent.h"
#include "Logger.h"

namespace Bountive
{
	Logger ModelComponent::logger = Logger("ModelComponent", Logger::Level::LEVEL_ALL);

	ModelComponent::ModelComponent(ModelComponent* parentComponent, ResourceMesh* mesh) :
		mParentComponent(parentComponent),
		mChildComponents(new std::vector<ModelComponent*>()),
		mMesh(mesh),
		mTransform(new Transform())
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating ModelComponent...");
	}


	ModelComponent::~ModelComponent()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting ModelComponent...");

		delete mTransform;

		for (GLuint i = 0; i < mChildComponents->size(); ++i)
		{
			if (mChildComponents->at(i) != nullptr)
			{
				delete mChildComponents->at(i);
			}
		}

		mChildComponents->clear();
		delete mChildComponents;

		delete mMesh;
	}


	void ModelComponent::setParentComponent(ModelComponent* mComponent)
	{
		mParentComponent = mComponent;
	}


	void ModelComponent::addChildComponent(ModelComponent* mComponent)
	{
		mChildComponents->push_back(mComponent);
	}


	void ModelComponent::setPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		mTransform->setPosition(x, y, z);
	}


	void ModelComponent::setRotation(GLfloat x, GLfloat y, GLfloat z)
	{
		mTransform->setRotation(x, y, z);
	}


	void ModelComponent::setScale(GLfloat scale)
	{
		mTransform->setScale(scale);
	}


	const Transform& ModelComponent::getTransform() const
	{
		return *mTransform;
	}


	ModelComponent* ModelComponent::getParentComponent() const
	{
		return mParentComponent;
	}


	ResourceMesh* ModelComponent::getMesh() const
	{
		return mMesh;
	}

	void ModelComponent::render(const GLdouble& DELTA_TIME)
	{
		mMesh->render(DELTA_TIME);
	}
}