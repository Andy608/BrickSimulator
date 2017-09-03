#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Transform.h"
#include "Logger.h"

namespace Bountive
{
	Logger Transform::logger = Logger("Transform", Logger::Level::LEVEL_ALL);
	glm::vec3 Transform::WORLD_UP = glm::vec3(0, 1, 0);
	glm::vec3 Transform::WORLD_RIGHT = glm::vec3(1, 0, 0);
	glm::vec3 Transform::WORLD_FORWARD = glm::vec3(0, 0, 1);

	Transform::Transform(glm::vec3 position, glm::vec3 rotation, GLfloat scale) :
		mPosition(position),
		mPrevPosition(position),
		mRotation(rotation),
		mScale(scale),
		mDimensions(glm::vec3(1, 1, 1))
	{

	}


	Transform::~Transform()
	{

	}


	void Transform::setRenderedPosition(glm::vec3 renderedPosition)
	{
		mRenderedPosition = renderedPosition;
	}


	void Transform::setPosition(glm::vec3 newPosition)
	{
		mPrevPosition = mPosition;
		mPosition = newPosition;
	}


	void Transform::setPosition(GLfloat xPosition, GLfloat yPosition, GLfloat zPosition)
	{
		mPrevPosition = mPosition;
		mPosition.x = xPosition;
		mPosition.y = yPosition;
		mPosition.z = zPosition;
	}


	const glm::vec3& Transform::getPosition() const
	{
		return mPosition;
	}


	const glm::vec3& Transform::getPrevPosition() const
	{
		return mPrevPosition;
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


	void Transform::setDimensions(GLfloat xDimension, GLfloat yDimension, GLfloat zDimension)
	{
		mDimensions.x = xDimension;
		mDimensions.y = yDimension;
		mDimensions.z = zDimension;
	}


	const glm::vec3& Transform::getDimensions() const
	{
		return mDimensions;
	}


	void Transform::setScale(GLfloat scale)
	{
		mScale = scale;
	}


	const GLfloat& Transform::getScale() const
	{
		return mScale;
	}


	const glm::mat4& Transform::getTransformationMatrix()
	{
		mTransformation = glm::mat4();

		mTransformation = glm::translate(mTransformation, mPosition);

		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.x), WORLD_RIGHT);
		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.y), WORLD_UP);
		mTransformation = glm::rotate(mTransformation, glm::radians(mRotation.z), WORLD_FORWARD);

		mTransformation = glm::scale(mTransformation, mDimensions * mScale);

		return mTransformation;
	}


	const GLfloat* Transform::getTransformationMatrixPtr()
	{
		return glm::value_ptr(getTransformationMatrix());
	}
}