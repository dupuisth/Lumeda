#include <Lumeda/Renderer/Light.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Core/Transform.h>

using namespace Lumeda;

sLightPassCounter::sLightPassCounter() : Counter()
{
    LUMEDA_PROFILE;
}

void sLightPassCounter::Increment(eLightType lightType)
{
    LUMEDA_PROFILE;
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
    LUMEDA_PROFILE;
    if (Counter.find(lightType) == Counter.end())
    {
        return 0;
    }
    return Counter[lightType];
}

void sLightPassCounter::Reset()
{
    LUMEDA_PROFILE;
    Counter = std::map<eLightType, int>();
}

void sLight::SendToShader(Shader* shader, Transform* transform, sLightPassCounter& counter)
{
    LUMEDA_PROFILE;
    if (LightType == eLightType::POINT)
    {
        int indice = counter.Current(LightType);
        std::string prefix = "u_PointLights[" + std::to_string(indice) + "].";
        shader->SetUniform(prefix + "position", transform->GetPosition());
        shader->SetUniform(prefix + "color", Color);
        shader->SetUniform(prefix + "polynomial", LightCharacteristics.Polyonomial);
        shader->SetUniform(prefix + "linear", LightCharacteristics.Linear);
        shader->SetUniform(prefix + "constant", LightCharacteristics.Constant);
        shader->SetUniform(prefix + "intensity", Intensity);
        counter.Increment(LightType);
    }
    else if (LightType == eLightType::SPOT)
    {
        int indice = counter.Current(LightType);
        std::string prefix = "u_SpotLights[" + std::to_string(indice) + "].";
        shader->SetUniform(prefix + "position", transform->GetPosition());
        shader->SetUniform(prefix + "direction", transform->GetForward());
        shader->SetUniform(prefix + "color", Color);
        shader->SetUniform(prefix + "polynomial", LightCharacteristics.Polyonomial);
        shader->SetUniform(prefix + "linear", LightCharacteristics.Linear);
        shader->SetUniform(prefix + "constant", LightCharacteristics.Constant);
        shader->SetUniform(prefix + "intensity", Intensity);
        counter.Increment(LightType);
    }
    else if (LightType == eLightType::DIRECTIONNAL)
    {
        int indice = counter.Current(LightType);
        std::string prefix = "u_DirectionalLights[" + std::to_string(indice) + "].";
        shader->SetUniform(prefix + "direction", transform->GetForward());
        shader->SetUniform(prefix + "color", Color);
        shader->SetUniform(prefix + "intensity", Intensity);
        counter.Increment(LightType);
    }
}
