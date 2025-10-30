#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gLightSpacePosition;
layout (location = 2) out vec3 gNormal;
layout (location = 3) out vec3 gAlbedo;
layout (location = 4) out float gPointLightsContribution;
layout (location = 5) out float gStencil;

in vec3 FragPos;
in vec4 FragPosLightSpace;
in vec3 Normal;

uniform vec3 diffuseColor;
uniform float pointLightsContribution;
uniform int writeStencil;

void main()
{    
    gPosition = FragPos;
    // project here already so we don't need to carry over w in the texture
    vec3 projectedLightSpaceCoordinates = FragPosLightSpace.xyz / FragPosLightSpace.w;
    projectedLightSpaceCoordinates = projectedLightSpaceCoordinates * 0.5 + 0.5;
    gLightSpacePosition = projectedLightSpaceCoordinates;
    gNormal = normalize(Normal);
    gAlbedo.rgb = diffuseColor;
    gPointLightsContribution = pointLightsContribution;
    
    if (writeStencil == 1)
    {
        gStencil = 0.0f;
    }
    else
    {
        gStencil = 1.0f;
    }
}