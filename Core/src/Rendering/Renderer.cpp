#include <stdafx.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Rendering/Renderer.h>
#include <Input/Input.h>

Renderer::Renderer()
{
    std::cout << "Creating Renderer" << std::endl;
}

Renderer::~Renderer()
{
}

bool Renderer::Intialize(int width, int height, const char* windowName)
{
    if (!glfwInit())
    {
        std::cout << "Could not initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (!(window = glfwCreateWindow(width, height, windowName, NULL, NULL)))
    {
        std::cout << "Could not create GLFW Window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        std::cout << "Could not initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, ResizeCallback);

    glClearColor(0.2, 0.2, 0.2, 1);
    
    return true;
}

void Renderer::Start()
{
    while (!glfwWindowShouldClose(window))
    {
        Input::Process(window);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }
}

void Renderer::Terminate()
{
    glfwTerminate();
}

void Renderer::ResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}