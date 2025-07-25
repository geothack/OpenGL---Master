#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 Tex;

layout (std140, binding = 0) uniform Camera
{
    mat4 Projection;
    mat4 View;
};

out vec2 coords;
out vec3 pos;

uniform mat4 Model;

void main()
{
	coords = Tex;
	pos = aPos;

	gl_Position = Projection * View * Model * vec4(aPos,1.0);
}