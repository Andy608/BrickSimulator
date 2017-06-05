#pragma once
#ifndef BOUNTIVE_VERTEX_H_
#define BOUNTIVE_VERTEX_H_

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

namespace Bountive
{
	struct Vertex
	{
	public:
		glm::vec3 mPosition;
		glm::vec3 mNormal;
		glm::vec2 mTextureCoords;
	};
}

#endif