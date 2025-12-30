#include <stdafx.h>

#include <Rendering/Shader.h>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

    // Setup Vertex Shader
    std::string sourceVertexShaderCode = ReadShaderFile(vertexPath);
    const char* vertexShaderCode = sourceVertexShaderCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    if (!VerifyShaderCompile(vertexShader, "Vertex"))
    {
        return;
    }
    
    // Setup Fragment Shader
    std::string sourceFragmentShaderCode = ReadShaderFile(fragmentPath);
    const char* fragmentShaderCode = sourceFragmentShaderCode.c_str();
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    if (!VerifyShaderCompile(fragmentShader, "Fragement"))
    {
        return;
    }

    // Setup Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    if (!VerifyShaderCompile(ID, "Program"))
    {
        return;
    }

    // Don't forget to delete the shaders after creating the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

std::string Shader::ReadShaderFile(const char* path)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure exception)
    {
        std::cout << "ERROR SHADER FILE COULD NOT BE READ" << std::endl;
        std::cout << exception.what() << std::endl;
        return nullptr;
    }

    return shaderCode;
}

bool Shader::VerifyShaderCompile(unsigned int shader, const char* shaderType)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error loading " << shaderType << " shader : " << infoLog << std::endl;
        return false;
    }

    return true;
}
