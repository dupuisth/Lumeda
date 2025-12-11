#include <Lumeda/Renderer/Light.h>
#include "Light.h"

using namespace Lumeda;

void sLightPassCounter::Increment(eLightType lightType)
{
    if (Counter.find(lightType) == Counter.end())
    {
        Counter[lightType] = 1;
    }
    else
    {
        Counter[lightType] += 1;
    }
}

int sLightPassCounter::Current(eLightType lightType)
{
    if (Counter.find(lightType) == Counter.end())
    {
        return 0;
    }
    return Counter[lightType];
}

void sLightPassCounter::Reset()
{
    Counter = std::map<eLightType, int>();
}

void sLight::SendToShader(std::shared_ptr<Shader> shader, const Transform* transform, sLightPassCounter& counter)
{
    if (LightType == eLightType::POINT)
    {

    }
    else if (LightType == eLightType::SPOT)
    {
    }
    else if (LightType == eLightType::DIRECTIONNAL)
    {
    }

    counter.Increment(LightType);
}
