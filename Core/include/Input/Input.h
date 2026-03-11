#pragma once
#include <stdafx.h>

#include <GLFW/glfw3.h>

#include <Rendering/Camera.h>

class Input
{
public:
    Input() {
        firstMouseCall = true;
        lastX = 0;
        lastY = 0;
    };
    ~Input() {};

    void Initialize(GLFWwindow* window, Camera* camera);
    void Process();
    static void MouseCallback(GLFWwindow* window, double posX, double posY);
private:
    bool firstMouseCall;
    float lastX;
    float lastY;

    GLFWwindow* window;
    Camera* camera;

    void OnMouseCallback(double posX, double posY);

};