#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace lab {
namespace opengl {

	namespace {
		const glm::vec3 k_defaultWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		const glm::vec3 k_defaultFront = glm::vec3(0.0f, 0.0f, -1.0f);

		const float k_defaultYaw = -90.0f;
		const float k_defaultPitch = 0.0f;
		const float k_defualtSpeed = 2.5f;
		const float k_defaultSensitivity = 0.1f;
		const float k_defaultZoom = 45.0f;
	}

	Camera::Camera(glm::vec3 position)
		: mPosition(position)
		, mUp(k_defaultWorldUp)
		, mYaw(k_defaultYaw)
		, mPitch(k_defaultPitch)
		, mFront(k_defaultFront)
		, mMovementSpeed(k_defualtSpeed)
		, mMouseSensitivity(k_defaultSensitivity)
		, mZoom(k_defaultZoom) {

		updateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: mPosition(glm::vec3(posX, posY, posZ))
		, mUp(glm::vec3(upX, upY, upZ))
		, mFront(k_defaultFront)
		, mYaw(yaw)
		, mPitch(pitch)
		, mMovementSpeed(k_defualtSpeed)
		, mMouseSensitivity(k_defaultSensitivity)
		, mZoom(k_defaultZoom) {
		
		updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix() const {
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	float Camera::getZoom() const {
		return mZoom;
	}

	void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
		float velocity = mMovementSpeed * deltaTime;

		if (direction == CameraMovement::Forward)
			mPosition += mFront * velocity;

		if (direction == CameraMovement::Backward)
			mPosition -= mFront * velocity;

		if (direction == CameraMovement::Left)
			mPosition -= mRight * velocity;

		if (direction == CameraMovement::Right)
			mPosition += mRight * velocity;
	}

	void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
		xoffset *= mMouseSensitivity;
		yoffset *= mMouseSensitivity;

		mYaw += xoffset;
		mPitch += yoffset;

		if (constrainPitch) {
			if (mPitch > 89.0f)
				mPitch = 89.0f;
			if (mPitch < -89.0f)
				mPitch = -89.0f;
		}

		updateCameraVectors();
	}

	void Camera::processMouseScroll(float yoffset) {
		if (mZoom >= 1.0f && mZoom <= 45.0f)
			mZoom -= yoffset;

		if (mZoom <= 1.0f)
			mZoom = 1.0f;

		if (mZoom >= 45.0f)
			mZoom = 45.0f;
	}

	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

		mFront = glm::normalize(front);

		mRight = glm::normalize(glm::cross(mFront, mUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));
	}
}
}

