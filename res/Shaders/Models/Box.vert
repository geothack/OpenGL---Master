#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 aOffset;
layout (location = 2) in vec3 aScale;

layout (std140, binding = 0) uniform Camera
{
    mat4 Projection;
    mat4 View;
};


uniform mat4 Model;

void main()
{
	vec3 meshPos = vec3(Pos * aScale);

	gl_Position = Projection * View * Model * vec4(meshPos + aOffset,1.0);
}