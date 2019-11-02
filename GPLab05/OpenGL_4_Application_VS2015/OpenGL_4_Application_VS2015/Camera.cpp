
#include "Camera.hpp"

namespace gps {

	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) {
		this->cameraPosition = cameraPosition;
		this->cameraTarget = cameraTarget;
		this->cameraDirection = glm::normalize(-cameraPosition + cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->cameraRightDirection = glm::normalize(glm::cross(cameraDirection,up));
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(cameraPosition,cameraTarget,glm::cross(cameraDirection,cameraRightDirection));
	}

	void Camera::move(MOVE_DIRECTION direction, float speed) {
		if (direction == MOVE_FORWARD) {
			cameraPosition += speed * cameraDirection;
			cameraTarget += speed * cameraDirection;
		}
		else if (direction == MOVE_BACKWARD) {
			cameraPosition -= speed * cameraDirection;
			cameraTarget -= speed * cameraDirection;
		}
		else if (direction == MOVE_RIGHT) {
			cameraPosition -= speed * cameraRightDirection;
			cameraTarget -= speed * cameraRightDirection;
		}
		else if (direction == MOVE_LEFT) {
			cameraPosition += speed * cameraRightDirection;
			cameraTarget += speed * cameraRightDirection;
		}
	}

	void Camera::rotate(float pitch, float yaw) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		cameraDirection = glm::rotate(glm::mat4(1.0f), yaw, glm::cross(cameraRightDirection, cameraDirection))*glm::vec4(cameraDirection, 0.0f);
		cameraDirection = glm::rotate(glm::mat4(1.0f), pitch, cameraRightDirection)*glm::vec4(cameraDirection, 0.0f);
		cameraRightDirection = glm::normalize(glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		cameraTarget = cameraPosition + cameraDirection;
	}
}