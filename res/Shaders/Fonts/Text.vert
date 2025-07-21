#version 460 core
layout (location = 0) in vec2 vertex; // <vec2 pos>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = projection * transform * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.xy;
    TexCoords.y = 1.0f - TexCoords.y;
}