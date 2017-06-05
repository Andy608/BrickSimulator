#pragma once
#ifndef BOUNTIVE_CAMERA_H_
#define BOUNTIVE_CAMERA_H_

#include <glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include "IUpdatable.h"

namespace Bountive
{
	class Transform;
	class Logger;

	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 lookAtPosition);
		virtual ~Camera();

		void updateViewMatrix();
		static void updateProjectionMatrix(GLint viewportWidth, GLint viewportHeight);

		virtual void update(const GLdouble& DELTA_TIME);

		Transform* getTransform() const;

		glm::mat4 getViewMatrix() const;
		const GLfloat* getViewMatrixPtr() const;

		static glm::mat4 getPerspectiveMatrix();
		static const GLfloat* getPerspectiveMatrixPtr();

		static glm::mat4 getOrthoMatrix();
		static const GLfloat* getOrthoMatrixPtr();

	private:
		static Logger logger;
		static const GLfloat NEAR_PLANE;
		static const GLfloat FAR_PLANE;
		static glm::mat4 perspectiveMatrix;
		static glm::mat4 orthoMatrix;
		
		glm::mat4 mViewMatrix;

		glm::vec3 mCameraForward;
		glm::vec3 mCameraUp;
		glm::vec3 mCameraRight;


		Transform* mTransform;

		glm::vec3 mLookAtPosition;
	};
}

#endif