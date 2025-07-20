#version 460 core

layout (location = 0) in vec3 Pos;


layout (std140, binding = 0) uniform Camera
{
    mat4 Projection;
    mat4 View;
};

uniform mat4 Model;


void main()
{
	gl_Position = Projection * View * Model * vec4(Pos,1.0);
}