#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 aOffset;
layout (location = 2) in vec3 aScale;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	vec3 meshPos = vec3(Pos * aScale);

	gl_Position = Projection * View * Model * vec4(meshPos + aOffset,1.0);
}