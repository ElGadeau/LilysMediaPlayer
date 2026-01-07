#include <stdafx.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <Rendering/Renderer.h>
#include <Input/Input.h>
#include <Rendering/Shader.h>

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

    return true;
}

void Renderer::Start()
{
    Shader myShader("Resource/Shaders/VertexShader.vert", "Resource/Shaders/FragmentShader.frag");

    SetupShader();

    myShader.Use();

    // Texture Loading
    int width, height, nrChannels;
    unsigned char* textureData = stbi_load("Resource/Textures/wall.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(textureData);

    // -----

    while (!glfwWindowShouldClose(window))
    {
        Input::Process(window);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.Use();

        glBindTexture(GL_TEXTURE_2D, texture1);
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
    glViewport(0, 0, width, height);
}

void Renderer::SetupShader()
{
    float verticesTriangle[] = {
     0.5f,  0.5f, 0.0f,    1.f, 0.f, 0.f,    1.f, 1.f,
     0.5f, -0.5f, 0.0f,    0.f, 1.f, 0.f,    1.f, 0.f,
    -0.5f, -0.5f, 0.0f,    0.f, 0.f, 1.f,    0.f, 0.f,
    -0.5f,  0.5f, 0.0f,    0.f, 1.f, 0.f,    0.f, 1.f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the vertex attribut pointer for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Setup the vertex attribut pointer for texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}