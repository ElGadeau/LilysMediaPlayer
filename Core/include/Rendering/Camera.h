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

	float GetYaw() { return yaw; }
	float SetYaw(float newYaw) { yaw = newYaw; }

	float GetPitch() { return pitch; }
	float SetPitch(float newPitch) { pitch = newPitch; }

	void UpdatePerspective(float cameraRatio);

	void Update();

private:
	glm::vec3 position;

	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;

	float yaw;
	float pitch;

	glm::mat4 viewMat;
	glm::mat4 perspectiveMat;

	void CalculateVectors();
};