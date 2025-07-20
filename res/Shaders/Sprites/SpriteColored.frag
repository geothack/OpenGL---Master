#version 460 core

out vec4 OutColor;

uniform vec3 Color;

void main()
{    
    OutColor = vec4(Color,1.0);
}  