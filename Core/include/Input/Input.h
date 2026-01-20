#pragma once
#include <stdafx.h>

#include <GLFW/glfw3.h>

#include <Rendering/Camera.h>

class Input
{
public:
    Input();
    ~Input();

    void Initialize();
    static void Process(GLFWwindow* window, Camera* camera);
};