#include <stdafx.h>

#include <Rendering/Texture.h>

#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(const char* path)
{
    // Texture Loading
    int width, height, nrChannels;
    unsigned char* textureData = stbi_load(path, &width, &height, &nrChannels, 0);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

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
}

void Texture::Use(unsigned int textureLayer)
{
    glActiveTexture(textureLayer);
    glBindTexture(GL_TEXTURE_2D, textureID);
}