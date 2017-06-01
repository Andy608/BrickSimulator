#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Transform.h"
#include "Logger.h"

namespace Bountive
{
	Logger Transform::logger = Logger("Transform", Logger::Level::LEVEL_ALL);

	glm::vec3 Transform::UP_VEC = glm::vec3(0, 1, 0);
	glm::vec3 Transform::RIGHT_VEC = glm::vec3(1, 0, 0);
	glm::vec3 Transform::FORWARD_VEC = glm::vec3(0, 0, 1);

	Transform::Transform() :
		Transform(glm::vec3())
	{

	}

	Transform::Transform(glm::vec3 position) :
		Transform(position, glm::vec3())
	{

	}


	Transform::Transform(glm::vec3 position, glm::vec3 rotation) :
		Transform(position, rotation, glm::vec3(1, 1, 1))
	{

	}
	
	
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
		mPosition(position),
		mRotation(rotation),
		mScale(scale)
	{

	}


	Transform::~Transform()
	{

	}


	void Transform::setPosition(GLfloat xPosition, GLfloat yPosition, GLfloat zPosition)
	{
		mPosition.x = xPosition;
		mPosition.y = yPosition;
		mPosition.z = zPosition;
	}


	const glm::vec3& Transform::getPosition() const
	{
		return mPosition;
	}


	void Transform::setRotation(GLfloat xRotation, GLfloat yRotation, GLfloat zRotation)
	{
		mRotation.x = xRotation;
		mRotation.y = yRotation;
		mRotation.z = zRotation;
	}


	const glm::vec3& Transform::getRotation() const
	{
		return mRotation;
	}


	void Transform::setScale(GLfloat xScale, GLfloat yScale, GLfloat zScale)
	{
		mScale.x = xScale;
		mScale.y = yScale;
		mScale.z = zScale;
	}


	const glm::vec3& Transform::getScale() const
	{
		return mScale;
	}


	const glm::mat4& Transform::getTransformationMatrix()
	{
		mTransformation = glm::mat4();

		mTransformation = glm::translate(mTransformation, mPosition);

		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.x), RIGHT_VEC);
		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.y), UP_VEC);
		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.z), FORWARD_VEC);

		mTransformation = glm::scale(mTransformation, mScale);

		return mTransformation;
	}


	const GLfloat* Transform::getTransformationMatrixPtr()
	{
		return glm::value_ptr(getTransformationMatrix());
	}
}