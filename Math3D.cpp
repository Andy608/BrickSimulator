#include "Math3D.h"

namespace Bountive
{
	glm::vec3 Math3D::lerpVec3(const glm::vec3& first, const glm::vec3& second, GLfloat alpha)
	{
		return alpha * first * (1 - alpha) * second;
	}
}