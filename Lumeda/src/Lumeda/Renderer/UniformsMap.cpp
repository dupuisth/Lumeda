#include <Lumeda/Renderer/UniformsMap.h>

#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Texture.h>

using namespace Lumeda;

#define sUniformsMap_BrainlessSend(map) \
for (const auto& [uniform, val] : map) { \
shader->SetUniform(uniform, val); \
}

void sUniformsMap::Send(std::shared_ptr<Shader> shader)
{
    sUniformsMap_BrainlessSend(Mat4);
    sUniformsMap_BrainlessSend(Vec2);
    sUniformsMap_BrainlessSend(Vec3);
    sUniformsMap_BrainlessSend(Float);
    sUniformsMap_BrainlessSend(Int);

    int textureSlot = 0;
    for (const auto& [uniform, val] : Texture)
    {
        val->Bind(textureSlot);
        shader->SetUniform(uniform, textureSlot++);
    }
}

#define sUniformsMap_SetImplementationMacro(type, map) void sUniformsMap::Set(const std::string& uniform, type val) \
{\
    LUMEDA_PROFILE; \
    map[uniform] = val; \
}
sUniformsMap_SetImplementationMacro(const glm::mat4&, Mat4)
sUniformsMap_SetImplementationMacro(const glm::vec3&, Vec3)
sUniformsMap_SetImplementationMacro(const glm::vec2&, Vec2)
sUniformsMap_SetImplementationMacro(float, Float)
sUniformsMap_SetImplementationMacro(int, Int)
sUniformsMap_SetImplementationMacro(std::shared_ptr<Texture2D>, Texture)