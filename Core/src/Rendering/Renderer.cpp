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

    return true;
}

void Renderer::Start()
{
    SetupShader();

    while (!glfwWindowShouldClose(window))
    {
        Input::Process(window);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);


        RenderTriangle();



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

void Renderer::SetupShader()
{


    // Setup Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    if (!VerifyShaderCompile(vertexShader))
    {
        return;
    }

    // Setup Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (!VerifyShaderCompile(fragmentShader))
    {
        return;
    }

    // Setup Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    if (!VerifyShaderCompile(shaderProgram))
    {
        return;
    }

    // Don't forget to delete the shaders after creating the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float verticesTriangle[] = {
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
    };

    // Setup VBO
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

    // Setup the vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool Renderer::VerifyShaderCompile(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error loading shader : " << infoLog << std::endl;
        return false;
    }

    return true;
}

void Renderer::RenderTriangle()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
