#include "Rendering/Camera.h"

Camera::Camera(glm::vec3 intialPosition)
{
	position = intialPosition;

	glm::vec3 cameraTarget = glm::vec3(0);
	forward = glm::normalize(position - cameraTarget);

	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	right = glm::normalize(glm::cross(worldUp, forward));

	up = glm::cross(forward, right);
}

glm::mat4 Camera::LookAt(glm::vec3 target)
{
	return glm::lookAt(position, target, up);
}

void Camera::Move(glm::vec3 newPosition)
{
	position = newPosition;
}
