#version 330 core
#define NUM_POINT_LIGHTS 2

struct Material
{
    vec3 specular;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
};

uniform int enableSsao;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform sampler2D ssaoPosition;
uniform sampler2D ssaoLightSpacePosition;
uniform sampler2D ssaoNormal;
uniform sampler2D ssaoAlbedo;
uniform sampler2D ssaoPointLightsContribution;
uniform sampler2D ssaoMap;
uniform sampler2D shadowMap;

in vec2 TexCoords;

out vec4 FragColor;

float CalculateShadow(vec3 projectedLightSpaceCoordinates)
{
    if (projectedLightSpaceCoordinates.z > 1.0)
    {
        return 0.0;
    }
    else
    {
        vec3 normal = vec3(0.0f, 1.0f, 0.0f);
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        float shadow = 0.0;
        float currentDepth = projectedLightSpaceCoordinates.z;
        float bias = max(0.005f * (1.0f - dot(normal, directionalLight.direction)), 0.005f);

        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, projectedLightSpaceCoordinates.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }
        }
        shadow /= 9.0;

        return shadow;
    }
}

vec3 CalculateDirectionalLight(vec3 materialColor, vec3 projectedLightSpaceCoordinates, vec3 normal, vec3 viewDirection, float ssao)
{
    // ambient
    vec3 ambient = directionalLight.ambient * materialColor * ssao;

    // diffuse
    vec3 lightDirection = normalize(-directionalLight.direction);
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = directionalLight.diffuse * diffuseFactor * materialColor;

    // specular
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
    vec3 specular = directionalLight.specular * specularFactor * material.specular;

    // shadow
    float shadow = CalculateShadow(projectedLightSpaceCoordinates);
    return (ambient + (1.0 - shadow) * (diffuse + specular)) * directionalLight.intensity;
}

vec3 CalculatePointLight(vec3 materialColor, float pointLightsContribution, PointLight pointLight, vec3 fragmentPosition, vec3 normal, vec3 viewDirection, float ssao)
{
    // ambient
    vec3 ambient = pointLight.ambient * materialColor * ssao;

    // diffuse
    vec3 lightDirection = normalize(pointLight.position - fragmentPosition);
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = pointLight.diffuse * diffuseFactor * materialColor;

    // specular
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
    vec3 specular = pointLight.specular * specularFactor * material.specular;

    // attenuation
    float distance = length(pointLight.position - fragmentPosition);
    float attenuation = 1.0 / (1.0f + 0.022f * distance + 0.0019f * (distance * distance));

    //ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

   return (ambient + diffuse + specular) * pointLight.intensity * pointLightsContribution;
}

void main()
{
    vec3 fragmentPosition = texture(ssaoPosition, TexCoords).rgb;
    vec3 projectedLightSpaceCoordinates = texture(ssaoLightSpacePosition, TexCoords).rgb;
    vec3 normal = texture(ssaoNormal, TexCoords).rgb; 
    vec3 materialColor = texture(ssaoAlbedo, TexCoords).rgb;
    float pointLightsContribution = texture(ssaoPointLightsContribution, TexCoords).r;

    float ssao;
    if (enableSsao == 1)
    {
        ssao = texture(ssaoMap, TexCoords).r;     
    }
    else 
    {
        ssao = 1.0f;
    }

    vec3 viewDirection  = normalize(-fragmentPosition); // view position is (0, 0, 0) because we are in camera space

    // Hack
    // TODO - fix clearing of color buffer with sky color
    if (materialColor == vec3(0.0f))
    {
        FragColor = vec4(0.329, 0.349, 0.4, 1.0f);  // sky color
    }
    else
    {
        vec3 color = CalculateDirectionalLight(materialColor, projectedLightSpaceCoordinates, normal, viewDirection, ssao);

        for(int i = 0; i < NUM_POINT_LIGHTS; i++)
        {
            color += CalculatePointLight(materialColor, pointLightsContribution, pointLights[i], fragmentPosition, normal, viewDirection, ssao);
        }

        FragColor = vec4(color, 1.0f);
    }
}