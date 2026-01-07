#pragma once

class Texture
{
public:
    unsigned int textureID;

    Texture(const char* path);

    void Use(unsigned int textureLayer);
};