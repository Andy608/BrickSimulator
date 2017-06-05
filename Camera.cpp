#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Camera.h"
#include "Transform.h"
#include "InputTracker.h"
#include "BrickSimulator.h"
#include "Logger.h"

namespace Bountive
{
	Logger Camera::logger = Logger("Camera", Logger::Level::LEVEL_ALL);
	const GLfloat Camera::NEAR_PLANE = 0.001f;
	const GLfloat Camera::FAR_PLANE = 100.0f;
	glm::mat4 Camera::perspectiveMatrix;
	glm::mat4 Camera::orthoMatrix;

	Camera::Camera(glm::vec3 position, glm::vec3 lookAtPosition) :
		mTransform(new Transform(position)),
		mLookAtPosition(lookAtPosition)
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Creating Camera...");
	}


	Camera::~Camera()
	{
		logger.log(Logger::Level::LEVEL_DEBUG, "Deleting Camera...");
		delete mTransform;
	}


	void Camera::updateViewMatrix()
	{
		mViewMatrix = glm::lookAt(mTransform->getPosition(), mLookAtPosition, mCameraUp);
	}


	void Camera::updateProjectionMatrix(GLint viewportWidth, GLint viewportHeight)
	{
		perspectiveMatrix = glm::mat4();

		perspectiveMatrix = glm::perspective(
			glm::radians(static_cast<GLfloat>(BrickSimulator::instance->getGameSettings()->getFieldOfView().getCustomInteger())),
			static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight),
			NEAR_PLANE,
			FAR_PLANE);

		orthoMatrix = glm::ortho(
			-static_cast<GLfloat>(viewportWidth) / 2,
			static_cast<GLfloat>(viewportWidth) / 2,
			-static_cast<GLfloat>(viewportHeight) / 2,
			static_cast<GLfloat>(viewportHeight) / 2,
			NEAR_PLANE, FAR_PLANE);
	}


	void Camera::update(const GLdouble& DELTA_TIME)
	{
		mCameraForward = glm::normalize(mTransform->getPosition() - mLookAtPosition);
		mCameraRight = glm::normalize(glm::cross(mCameraForward, Transform::WORLD_UP));
		mCameraUp = glm::cross(mCameraRight, mCameraForward);

		if (InputTracker::instance->getCameraForwardKey().isPressed())
		{
			logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mTransform->getPosition().x) + ", " + 
				std::to_string(mTransform->getPosition().y) + ", " + 
				std::to_string(mTransform->getPosition().z));
			mTransform->setPosition(mTransform->getPosition().x, mTransform->getPosition().y, mTransform->getPosition().z - 1);
		}
		
		if (InputTracker::instance->getCameraBackwardKey().isPressed())
		{
			logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mTransform->getPosition().x) + ", " +
				std::to_string(mTransform->getPosition().y) + ", " +
				std::to_string(mTransform->getPosition().z));
			mTransform->setPosition(mTransform->getPosition().x, mTransform->getPosition().y, mTransform->getPosition().z + 1);
		}

		updateViewMatrix();
	}


	Transform* Camera::getTransform() const
	{
		return mTransform;
	}


	glm::mat4 Camera::getViewMatrix() const
	{
		return mViewMatrix;
	}


	const GLfloat* Camera::getViewMatrixPtr() const
	{
		return glm::value_ptr(mViewMatrix);
	}


	glm::mat4 Camera::getPerspectiveMatrix()
	{
		return perspectiveMatrix;
	}


	const GLfloat* Camera::getPerspectiveMatrixPtr()
	{
		return glm::value_ptr(perspectiveMatrix);
	}


	glm::mat4 Camera::getOrthoMatrix()
	{
		return orthoMatrix;
	}


	const GLfloat* Camera::getOrthoMatrixPtr()
	{
		return glm::value_ptr(orthoMatrix);
	}
}