#version 460 core

in vec2 Coords;

out vec4 Color;

uniform sampler2D Image;

void main()
{
	Color = texture(Image,Coords);
}