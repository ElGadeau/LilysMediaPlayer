#include "stdafx.h"
#include "Input/Input.h"

#include <Utils/Time.h>

void Input::Process(GLFWwindow* window, Camera* camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = 1.5f *Time().GetDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->Move(camera->GetForward() * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->Move(-camera->GetForward() * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->Move(-camera->GetRight() * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->Move(camera->GetRight() * cameraSpeed);
    }
}
