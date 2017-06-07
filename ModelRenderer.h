#pragma once
#ifndef BOUNTIVE_MODELRENDERER_H_
#define BOUNTIVE_MODELRENDERER_H_

#include "Renderer.h"
#include "Entity.h"

namespace Bountive
{
	class ResourceShaderProgram;
	class RenderManager;
	class Logger;

	class ModelRenderer : public Renderer
	{
	public:
		ModelRenderer(RenderManager& renderManager);
		~ModelRenderer();

		void render(const GLdouble& DELTA_TIME, const std::vector<Entity*>& MODEL_LIST, const ResourceShaderProgram& activeShaderProgram);

	private:
		static Logger logger;
	};
}

#endif