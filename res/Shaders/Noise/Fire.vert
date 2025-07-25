#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

layout (std140, binding = 0) uniform Camera
{
    mat4 Projection;
    mat4 View;
};

out vec2 TexCoords;

uniform mat4 Model;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}