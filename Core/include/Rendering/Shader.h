#pragma once
#include <stdafx.h>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void Use();

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);

private:
    std::string ReadShaderFile(const char* path);

    bool VerifyShaderCompile(unsigned int shader, const char* shaderType);
};