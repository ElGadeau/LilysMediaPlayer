#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, float cameraRatio, float fov);
	void LookAt(glm::vec3 target);
	void Move(glm::vec3 newPosition);

	glm::vec3 GetUp() { return up; }
	glm::vec3 GetRight() { return right; }
	glm::vec3 GetForward() { return forward; }
	glm::vec3 GetPosition() { return position; }

	glm::mat4 GetPerspective() { return perspectiveMat; }
	glm::mat4 GetView() { return viewMat; }

	void UpdatePerspective(float cameraRatio);

private:
	glm::vec3 position;

	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;


	glm::mat4 viewMat;
	glm::mat4 perspectiveMat;
};