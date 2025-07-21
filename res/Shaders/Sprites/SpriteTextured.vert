#version 460 core
layout (location = 0) in vec4 vertex; 

out vec2 TexCoords;

layout (std140, binding = 1) uniform SpriteCamera
{
    mat4 Projection;
};

uniform mat4 Model;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = Projection * Model * vec4(vertex.xy, 0.0, 1.0);
}