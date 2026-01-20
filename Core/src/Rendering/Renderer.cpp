#include <stdafx.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Rendering/Renderer.h>
#include <Input/Input.h>
#include <Rendering/Shader.h>
#include <Rendering/Texture.h>
#include <Rendering/Camera.h>

#include <Utils/Time.h>

//Static members
int Renderer::Width = 0;
int Renderer::Height = 0;
float Renderer::screenRatio = 0;


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

    Width = width;
    Height = height;

    screenRatio = (float)Width / (float)Height;

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, ResizeCallback);

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Renderer::Start()
{
    Time().CalculateDeltaTime();

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    Shader myShader("Resource/Shaders/VertexShader.vert", "Resource/Shaders/FragmentShader.frag");
    Texture firstTexture("Resource/Textures/container.jpg");
    Texture secondTexture("Resource/Textures/wall.jpg");

    Camera myCamera(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), screenRatio, 90.f);

    SetupShader();

    myShader.Use();

    myShader.SetInt("firstTexture", 0);
    myShader.SetInt("secondTexture", 1);


    myShader.SetMatrix4("projection", myCamera.GetPerspective());
    myShader.SetMatrix4("view", myCamera.GetView());


    const float radius = 10.f;


    while (!glfwWindowShouldClose(window))
    {
        Input::Process(window, &myCamera);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.Use();

        firstTexture.Use(GL_TEXTURE0);
        secondTexture.Use(GL_TEXTURE1);

        glBindVertexArray(VAO);

        myCamera.LookAt(myCamera.GetPosition() + myCamera.GetForward());
        myShader.SetMatrix4("view", myCamera.GetView());

        glDrawArrays(GL_TRIANGLES, 0, 36);

        int cubes = sizeof(cubePositions) / sizeof(glm::vec3);

        for (unsigned int i = 0; i < cubes; i++)
        {
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.SetMatrix4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::Terminate()
{
    glfwTerminate();
}

void Renderer::ResizeCallback(GLFWwindow* window, int width, int height)
{
    Width = width;
    Height = height;

    screenRatio = (float)Width / (float)Height;

    glViewport(0, 0, width, height);
}

void Renderer::SetupShader()
{
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };



    // Setup VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Setup the vertex attribute pointer for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the vertex attribute pointer for texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}