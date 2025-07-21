#version 460 core

in vec2 Coords;

out vec4 outColor;

uniform vec3 Color;

void main()
{	
	outColor = vec4(Color,1.0);
}