#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 TexCoords;
out vec3 WorldPos;
out vec3 ViewPos;

void main()
{
    TexCoords = aPos + 0.5;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    ViewPos = vec3(view * vec4(WorldPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
