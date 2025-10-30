#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec4 FragPosLightSpace;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpace;

void main()
{
    vec4 viewPos = view * model * vec4(aPos, 1.0);
    FragPos = viewPos.xyz;

    vec3 fragmentPositionModelSpace = vec3(model * vec4(aPos, 1.0));
    FragPosLightSpace = lightSpace * vec4(fragmentPositionModelSpace, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(view * model)));
    Normal = normalMatrix * aNormal;
    
    gl_Position = projection * viewPos;
}