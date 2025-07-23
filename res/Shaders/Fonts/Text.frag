#version 460 core
in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D text;
uniform vec3 Color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    outColor = vec4(Color, 1.0) * sampled;
}