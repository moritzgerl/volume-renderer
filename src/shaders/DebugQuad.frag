#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform int isSingleChannel;
uniform sampler2D colorTexture;

void main()
{
    vec3 color = vec3(0.0f);

    if (isSingleChannel == 1)
    {
        float value = texture(colorTexture, TexCoords).r;
        color = vec3(value);
    }
    else if (isSingleChannel == 0)
    {
        color = texture(colorTexture, TexCoords).rgb;
    }
    
    FragColor = vec4(color, 1.0);
}