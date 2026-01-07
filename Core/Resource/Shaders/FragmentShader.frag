#version 460 core

out vec4 fragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

void main()
{
    fragColor = mix(texture(firstTexture, texCoord), texture(secondTexture, texCoord), 0.5);
}