#include <GLM\gtc\matrix_transform.hpp>
#include "FreeRoamCamera.h"
#include "InputTracker.h"
#include "Transform.h"
#include "WindowSizeCallback.h"
#include "Logger.h"

namespace Bountive
{
	Logger FreeRoamCamera::logger = Logger("FreeRoamCamera", Logger::Level::LEVEL_ALL);

	FreeRoamCamera::FreeRoamCamera(glm::vec3 position, GLfloat cameraSpeed) :
		Camera(position, glm::vec3(0, 0, 1)),
		mCameraSpeed(cameraSpeed),
		mZoomAmount(1.0f),
		mSensitivity(12.0f),
		mCameraRotation(glm::vec3())
	{
		
	}


	FreeRoamCamera::~FreeRoamCamera()
	{

	}


	void FreeRoamCamera::update(const GLdouble& DELTA_TIME)
	{
		if (InputTracker::instance->getCameraForwardKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() - (mCameraForward * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		if (InputTracker::instance->getCameraBackwardKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() + (mCameraForward * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		if (InputTracker::instance->getCameraLeftKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() + (mCameraRight * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		if (InputTracker::instance->getCameraRightKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() - (mCameraRight * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		if (InputTracker::instance->getCameraUpKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() + (Transform::WORLD_UP * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		if (InputTracker::instance->getCameraDownKey().isPressed())
		{
			mTransform->setPosition(mTransform->getPosition() - (Transform::WORLD_UP * mCameraSpeed * static_cast<GLfloat>(DELTA_TIME)));
		}

		//mLookAtPosition = mTransform->getPosition() + (Transform::WORLD_FORWARD * mZoomAmount);
		
		glm::vec2 cameraRot = (InputTracker::instance->getCursorPosition() - InputTracker::instance->getLastCursorPosition());
		

		mCameraRotation.x = -cameraRot.x;
		mCameraRotation.y = -cameraRot.y;

		mPitch += mCameraRotation.y * static_cast<GLfloat>(DELTA_TIME) * mSensitivity;
		mYaw += mCameraRotation.x * static_cast<GLfloat>(DELTA_TIME) * mSensitivity;

		if (mYaw >= 360.0f) mYaw -= 360.0f;
		if (mYaw <= -360.0f) mYaw += 360.0f;

		if (mPitch <= -89.0f) mPitch = -89.0f;
		if (mPitch >= 89.0f) mPitch = 89.0f;

		//logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(cameraRot.x) + " " + std::to_string(cameraRot.y));

		glm::vec3 front;
		front.x = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
		front.y = sin(glm::radians(mPitch));
		front.z = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));

		//logger.log(Logger::Level::LEVEL_DEBUG, std::to_string(mLookAtPosition.x) + " " + std::to_string(mLookAtPosition.y) + " " + std::to_string(mLookAtPosition.z));
		mLookAtPosition = mTransform->getPosition() + glm::normalize(front);

		Camera::update(DELTA_TIME);
	}
}