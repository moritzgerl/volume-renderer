#ifndef MAKE_DEFAULT_POINT_LIGHTS_H
#define MAKE_DEFAULT_POINT_LIGHTS_H

#include <vector>

#include <lights/PointLight.h>

namespace Factory
{
    std::vector<PointLight> MakeDefaultPointLights(unsigned int numPointLights);
}

#endif
