#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position);
	glm::mat4 LookAt(glm::vec3 target);
	void Move(glm::vec3 newPosition);

	glm::vec3 GetUp() { return up; }
	glm::vec3 GetRight() { return right; }
	glm::vec3 GetForward() { return forward; }
	glm::vec3 GetPosition() { return position; }

private:
	glm::vec3 position;

	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;
};