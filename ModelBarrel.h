#pragma once
#ifndef BOUNTIVE_MODELBARREL_H_
#define BOUNTIVE_MODELBARREL_H_

#include "ResourceModel.h"

namespace Bountive
{
	class ModelBarrel : public ResourceModel
	{
	public:
		ModelBarrel();
		virtual ~ModelBarrel();

		virtual void load();

		virtual void update(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;
	};
}

#endif