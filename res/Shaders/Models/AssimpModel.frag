#version 460 core

in vec2 Coords;

out vec4 outColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	vec4 diffColor = texture(diffuse0,Coords);
	vec4 specColor = texture(specular0,Coords);

	vec4 combine = mix(diffColor,specColor,0.5);
	
	outColor = combine;
}