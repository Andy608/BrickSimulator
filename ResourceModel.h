#pragma once
#ifndef BOUNTIVE_RESOURCEMODEL_H_
#define BOUNTIVE_RESOURCEMODEL_H_

#include <vector>
#include "Resource.h"
#include "ModelComponent.h"
#include "IUpdatable.h"
#include "IRenderable.h"

namespace Bountive
{
	class Logger;

	class ResourceModel : public Resource, public IUpdatable, public IRenderable
	{
	public:
		ResourceModel(std::string RESOURCE_ID);
		virtual ~ResourceModel();

		virtual void load();
		virtual void unload();

		virtual void update(const GLdouble& DELTA_TIME) = 0;
		virtual void render(const GLdouble& DELTA_TIME);

	protected:
		std::vector<ModelComponent*>* mModelComponents;

	private:
		static Logger logger;
	};
}

#endif