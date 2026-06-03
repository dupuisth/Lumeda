#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>
#include <glm/glm.hpp>

namespace Lumeda
{
class Shader;

enum eLightType
{
    POINT,
    SPOT,
    DIRECTIONNAL
};

struct sLightCharacteristics
{
    float Polyonomial;
    float Linear;
    float Constant;
};

struct sLightPassCounter
{
    sLightPassCounter();

    std::map<eLightType, int> Counter;

    void Increment(eLightType lightType);
    int Current(eLightType lightType);
    void Reset();
};

struct sLight
{
    eLightType LightType;
    sLightCharacteristics LightCharacteristics;
    float Intensity;
    float AngleRad;
    glm::vec3 Color;

    void SendToShader(Shader* shader, Transform* transform, sLightPassCounter& counter);
};
} // namespace Lumeda