#version 460 core

out vec4 Color;
in vec3 color;
  
void main()
{
    Color = vec4(color, 1.0);
}