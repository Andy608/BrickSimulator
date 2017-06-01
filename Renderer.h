#pragma once
#ifndef BOUNTIVE_RENDERER_H_
#define BOUNTIVE_RENDERER_H_

#include <vector>
#include "Entity.h"
#include "IUpdatable.h"
#include "IRenderable.h"

namespace Bountive
{
	class RenderManager;
	class Logger;

	class Renderer
	{
	public:
		Renderer(RenderManager& renderManager);
		virtual ~Renderer();

	protected:
		RenderManager& mRenderManager;

	private:
		static Logger logger;
	};
}

#endif