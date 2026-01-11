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

    return true;
}

void Renderer::Start()
{
    Shader myShader("Resource/Shaders/VertexShader.vert", "Resource/Shaders/FragmentShader.frag");
    Texture firstTexture("Resource/Textures/container.jpg");
    Texture secondTexture("Resource/Textures/wall.jpg");

    SetupShader();

    myShader.Use();

    myShader.SetInt("firstTexture", 0);
    myShader.SetInt("secondTexture", 1);

    glm::mat4 trans(1.f);
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    trans = glm::rotate(trans, glm::radians(45.f), glm::vec3(0.5f, 0.5f, 0.f));

    myShader.SetMatrix4("model", trans);


    glm::mat4 view(1.f);
    glm::mat4 projection(1.f);

    projection = glm::perspective(glm::radians(45.f), screenRatio, 0.1f, 100.f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

    myShader.SetMatrix4("projection", projection);
    myShader.SetMatrix4("view", view);

    while (!glfwWindowShouldClose(window))
    {
        Input::Process(window);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.Use();

        firstTexture.Use(GL_TEXTURE0);
        secondTexture.Use(GL_TEXTURE1);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    float verticesTriangle[] = {
     0.5f,  0.5f, 0.0f,    1.f, 1.f,
     0.5f, -0.5f, 0.0f,    1.f, 0.f,
    -0.5f, -0.5f, 0.0f,    0.f, 0.f,
    -0.5f,  0.5f, 0.0f,    0.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Setup VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Setup the vertex attribute pointer for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the vertex attribut pointer for texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}