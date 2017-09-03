#pragma once
#ifndef BOUNTIVE_MATH3D_H_
#define BOUNTIVE_MATH3D_H_

#include <glew.h>
#include <glm\vec3.hpp>

namespace Bountive
{
	class Math3D
	{
	public:
		static glm::vec3 lerpVec3(const glm::vec3& first, const glm::vec3& second, GLfloat alpha);
	};
}

#endif