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
		static glm::vec3 WORLD_UP;
		static glm::vec3 WORLD_RIGHT;
		static glm::vec3 WORLD_FORWARD;

		Transform(glm::vec3 position = glm::vec3(), glm::vec3 rotation = glm::vec3(), GLfloat scale = 1.0f);
		~Transform();

		void setPosition(GLfloat xPosition, GLfloat yPosition, GLfloat zPosition);
		const glm::vec3& getPosition() const;

		void setRotation(GLfloat xRotation, GLfloat yRotation, GLfloat zRotation);
		const glm::vec3& getRotation() const;

		void setDimensions(GLfloat xDimension, GLfloat yDimension, GLfloat zDimension);
		const glm::vec3& getDimensions() const;

		void setScale(GLfloat scale);
		const GLfloat& getScale() const;

		const glm::mat4& getTransformationMatrix();
		const GLfloat* getTransformationMatrixPtr();

	private:
		static Logger logger;

		glm::mat4 mTransformation;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mDimensions;

		GLfloat mScale;
	};
}

#endif