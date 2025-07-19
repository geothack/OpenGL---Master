#version 460 core

out vec4 outColor;

uniform vec3 Color;

void main()
{
	outColor = vec4(Color.x,Color.y,Color.z,1.0);
}