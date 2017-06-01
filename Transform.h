#pragma once
#ifndef BOUNTIVE_TRANSFORM_H_
#define BOUNTIVE_TRANSFORM_H_

#include <glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

namespace Bountive
{
	class Logger;

	class Transform
	{
	public:
		//right handed system
		static glm::vec3 UP_VEC;
		static glm::vec3 RIGHT_VEC;
		static glm::vec3 FORWARD_VEC;

		Transform();
		Transform(glm::vec3 position);
		Transform(glm::vec3 position, glm::vec3 rotation);
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		~Transform();

		void setPosition(GLfloat xPosition, GLfloat yPosition, GLfloat zPosition);
		const glm::vec3& getPosition() const;

		void setRotation(GLfloat xRotation, GLfloat yRotation, GLfloat zRotation);
		const glm::vec3& getRotation() const;

		void setScale(GLfloat xScale, GLfloat yScale, GLfloat zScale);
		const glm::vec3& getScale() const;

		const glm::mat4& getTransformationMatrix();
		const GLfloat* getTransformationMatrixPtr();

	private:
		static Logger logger;

		glm::mat4 mTransformation;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;
	};
}

#endif