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
    bool VerifyShaderCompile(unsigned int shader);
    void RenderTriangle();

    // Members

    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;

    const char* vertexShaderSource = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

};