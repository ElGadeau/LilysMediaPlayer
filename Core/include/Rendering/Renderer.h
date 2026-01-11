#pragma once

#include <GLFW/glfw3.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Intialize(int width, int height, const char* windowName);
    void Start();
    void Terminate();

private:
    
    // Methods
    GLFWwindow* window;

    static void ResizeCallback(GLFWwindow* window, int width, int height);
    void SetupShader();

    // Members

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    static int Width;
    static int Height;
    static float screenRatio;
};