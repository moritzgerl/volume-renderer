#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
in vec3 WorldPos;
in vec3 ViewPos;

uniform sampler3D volumeTexture;
uniform mat4 view;
uniform vec3 cameraPos;
uniform float stepSize;
uniform int maxSteps;
uniform float densityMultiplier;

vec3 GetRayDirection()
{
    return normalize(WorldPos - cameraPos);
}

bool IntersectBox(vec3 rayOrigin, vec3 rayDir, out float tNear, out float tFar)
{
    vec3 boxMin = vec3(0.0);
    vec3 boxMax = vec3(1.0);

    vec3 invRayDir = 1.0 / rayDir;
    vec3 tMin = (boxMin - rayOrigin) * invRayDir;
    vec3 tMax = (boxMax - rayOrigin) * invRayDir;

    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);

    tNear = max(max(t1.x, t1.y), t1.z);
    tFar = min(min(t2.x, t2.y), t2.z);

    return tFar > tNear && tFar > 0.0;
}

vec4 SampleVolume(vec3 pos)
{
    if (pos.x < 0.0 || pos.x > 1.0 ||
        pos.y < 0.0 || pos.y > 1.0 ||
        pos.z < 0.0 || pos.z > 1.0)
    {
        return vec4(0.0);
    }

    float density = texture(volumeTexture, pos).r;
    density *= densityMultiplier;

    vec3 color = vec3(density);
    float alpha = density;

    return vec4(color, alpha);
}

void main()
{
    vec3 rayOrigin = TexCoords;
    vec3 rayDir = GetRayDirection();

    float tNear, tFar;
    
    if (!IntersectBox(rayOrigin, rayDir, tNear, tFar))
    {
        discard;
    }

    if (tNear < 0.0)
    {
        tNear = 0.0;
    }

    vec3 rayStart = rayOrigin + rayDir * tNear;
    vec3 rayStop = rayOrigin + rayDir * tFar;

    float rayLength = distance(rayStop, rayStart);
    vec3 rayStep = normalize(rayStop - rayStart) * stepSize;

    vec3 currentPos = rayStart;
    vec4 accumulatedColor = vec4(0.0);

    int steps = min(maxSteps, int(rayLength / stepSize));

    for (int i = 0; i < steps; ++i)
    {
        vec4 sampleColor = SampleVolume(currentPos);

        sampleColor.rgb *= sampleColor.a;
        accumulatedColor += (1.0 - accumulatedColor.a) * sampleColor;

        if (accumulatedColor.a >= 0.95)
        {
            break;
        }

        currentPos += rayStep;
    }

    FragColor = accumulatedColor;
}
