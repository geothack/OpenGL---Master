#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Tex;

out vec2 Coords;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


void main()
{
	Coords = Tex;
	gl_Position = Projection * View * Model * vec4(Pos,1.0);
}