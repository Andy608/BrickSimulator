#pragma once
#ifndef BOUNTIVE_MODELCOMPONENT_H_
#define BOUNTIVE_MODELCOMPONENT_H_

#include <vector>
#include "ResourceMesh.h"
#include "Transform.h"
#include "IRenderable.h"

namespace Bountive
{
	class Logger;

	class ModelComponent : public IRenderable
	{
	public:
		ModelComponent(ModelComponent* parentComponent, ResourceMesh* mesh);
		~ModelComponent();

		void setParentComponent(ModelComponent* mComponent);
		void addChildComponent(ModelComponent* mComponent);

		void setPosition(GLfloat x, GLfloat y, GLfloat z);
		void setRotation(GLfloat x, GLfloat y, GLfloat z);
		void setScale(GLfloat scale);

		virtual void render(const GLdouble& DELTA_TIME);

		ModelComponent* getParentComponent() const;
		const Transform& getTransform() const;
		ResourceMesh* getMesh() const;

	private:
		static Logger logger;

		ModelComponent* mParentComponent;
		std::vector<ModelComponent*>* mChildComponents;
		ResourceMesh* mMesh;
		Transform* mTransform;
	};
}

#endif