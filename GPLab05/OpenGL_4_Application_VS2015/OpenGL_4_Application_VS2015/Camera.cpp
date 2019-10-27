
#include "Camera.hpp"

namespace gps {

	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) {
		this->cameraPosition = cameraPosition;
		this->cameraTarget = cameraTarget;
		this->cameraDirection = glm::normalize(cameraPosition - cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->cameraRightDirection = glm::normalize(glm::cross(up, cameraDirection));
	}

	//glm::mat4 getViewMatrix() {
	//	return glm::lookAt(getCameraPosition,cameraTarget,glm::cross(cameraDirection,cameraRightDirection));
	//}

	//void move(MOVE_DIRECTION direction, float speed) {
	//	if (direction == MOVE_FORWARD) {
	//		cameraPosition += speed * cameraDirection;
	//	}
	//	else if (direction == MOVE_BACKWARD) {
	//		cameraPosition -= speed * cameraDirection;
	//	}
	//	else if (direction == MOVE_RIGHT) {
	//		cameraPosition += speed * cameraRightDirection;
	//	}
	//	else if (direction == MOVE_LEFT) {
	//		cameraPosition -= speed * cameraRightDirection;
	//	}
	//}

	//void rotate(float pitch, float yaw) {
	//	if (pitch > 89.0f)
	//		pitch = 89.0f;
	//	if (pitch < -89.0f)
	//		pitch = -89.0f;
	//	glm::vec3 front;
	//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	front.y = sin(glm::radians(pitch));
	//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	cameraDirection = glm::normalize(front);
	//	cameraRightDirection = glm::normalize(glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	//}
}