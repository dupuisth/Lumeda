#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>
#include <map>

namespace Lumeda
{
    class Shader;
    class Texture2D;

    struct sUniformsMap
    {
    public:
#define sUniformsMap_SetHeaderMacro(type) void Set(const std::string& uniform, type val);
        sUniformsMap_SetHeaderMacro(const glm::mat4&);
        sUniformsMap_SetHeaderMacro(const glm::vec3&);
        sUniformsMap_SetHeaderMacro(const glm::vec2&);
        sUniformsMap_SetHeaderMacro(float);
        sUniformsMap_SetHeaderMacro(int);
        sUniformsMap_SetHeaderMacro(std::shared_ptr<Texture2D>);

        void Send(std::shared_ptr<Shader> shader);

    public:
        std::map<std::string, glm::mat4> Mat4;
        std::map<std::string, glm::vec3> Vec3;
        std::map<std::string, glm::vec2> Vec2;
        std::map<std::string, float> Float;
        std::map<std::string, int> Int;
        std::map<std::string, std::shared_ptr<Texture2D>> Texture;
    };
}