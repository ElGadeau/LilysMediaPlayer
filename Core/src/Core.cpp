// Core.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Test.h>



int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Could not initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        std::cout << "Could not initialize GLAD" << std::endl;
        return -1;
    }

    glClearColor(1, 0, 0, 1);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}