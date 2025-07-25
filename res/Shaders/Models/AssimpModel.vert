#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Tex;

layout (std140, binding = 0) uniform Camera
{
    mat4 Projection;
    mat4 View;
};

out vec2 Coords;

uniform mat4 Model;

void main()
{
	Coords = Tex;
	gl_Position = Projection * View * Model * vec4(Pos,1.0);
}