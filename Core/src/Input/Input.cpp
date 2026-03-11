#include "stdafx.h"
#include "Input/Input.h"

#include <Utils/Time.h>

void Input::Initialize(GLFWwindow* window, Camera* camera)
{
    this->window = window;
    this->camera = camera;
}

void Input::Process()
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

void Input::MouseCallback(GLFWwindow* window, double pPosX, double pPosY)
{
    Input* currentInput = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

    currentInput->OnMouseCallback(pPosX, pPosY);
}

void Input::OnMouseCallback(double pPosX, double pPosY)
{
    float posX = static_cast<float>(pPosX);
    float posY = static_cast<float>(pPosY);

    if (firstMouseCall)
    {
        lastX = posX;
        lastY = posY;
        firstMouseCall = false;
    }

    float xOffset = posX - lastX;
    float yOffset = posY - lastY;

    lastX = posX;
    lastY = posY;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera->SetYaw(camera->GetYaw() + xOffset);
    camera->SetPitch(camera->GetPitch() + yOffset);

    if (camera->GetPitch() > 89.f)
    {
        camera->SetPitch(89.f);
    }
    if (camera->GetPitch() < -89.f)
    {
        camera->SetPitch(-89.f);
    }

    camera->Update();
}