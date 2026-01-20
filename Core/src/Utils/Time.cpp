#include "Utils/Time.h"

#include <GLFW/glfw3.h>

float Time::deltaTime = 0;
float Time::lastFrame = 0;

float Time::GetDeltaTime()
{
	return deltaTime;
}

void Time::CalculateDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

