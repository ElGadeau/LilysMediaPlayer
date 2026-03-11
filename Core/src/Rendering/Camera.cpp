#include "Rendering/Camera.h"

Camera::Camera(glm::vec3 intialPosition, glm::vec3 target, float cameraRatio, float fov)
{
	yaw = -90.f;
	pitch = 0.f;

	position = intialPosition;

	glm::vec3 cameraTarget = glm::vec3(0);
	forward = glm::normalize(cameraTarget - position);

	CalculateVectors();
	
	LookAt(target);
	perspectiveMat = glm::perspective(glm::radians(fov / cameraRatio), cameraRatio, 0.1f, 100.f);
}

void Camera::LookAt(glm::vec3 target)
{
	viewMat = glm::lookAt(position, target, up);
}

void Camera::Move(glm::vec3 newPosition)
{
	position += newPosition;
}

void Camera::UpdatePerspective(float cameraRatio)
{
	perspectiveMat = glm::perspective(glm::radians(45.f), cameraRatio, 0.1f, 100.f);
}

void Camera::Update()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);

	CalculateVectors();
}

void Camera::CalculateVectors()
{
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::cross(right, forward);
}