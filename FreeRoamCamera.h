#pragma once
#ifndef FREEROAMCAMERA_H_
#define FREEROAMCAMERA_H_
#include "Camera.h"

namespace Bountive
{
	class FreeRoamCamera : public Camera
	{
	public:
		FreeRoamCamera(glm::vec3 position, GLfloat cameraSpeed);
		virtual ~FreeRoamCamera();

		virtual void update(const GLdouble& DELTA_TIME);

	private:
		static Logger logger;

		GLfloat mCameraSpeed;
		GLfloat mZoomAmount;
		GLfloat mSensitivity;

		GLfloat mYaw;
		GLfloat mPitch;

		glm::vec3 mCameraRotation;
	};
}

#endif