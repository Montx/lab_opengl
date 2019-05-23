#pragma once

#include <glm/glm.hpp>

namespace lab {
namespace opengl {

	enum class CameraMovement {
		Forward,
		Backward,
		Left,
		Right
	};

	class Camera {
	public:
		Camera(glm::vec3 position);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		glm::mat4 getViewMatrix() const;

		float getZoom() const;

		void processKeyboard(CameraMovement direction, float deltaTime);
		void processMouseMovement(float xoffset, float yoffset, bool constrainPitch);
		void processMouseScroll(float yoffset);

	private:
		void updateCameraVectors();

		glm::vec3 mPosition;
		glm::vec3 mFront;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;

		float mYaw;
		float mPitch;

		float mMovementSpeed;
		float mMouseSensitivity;
		float mZoom;
	};

}
}