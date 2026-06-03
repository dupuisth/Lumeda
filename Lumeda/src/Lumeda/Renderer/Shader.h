#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Lumeda
{
struct sShaderPrepareData
{
  public:
    float Time = 0.0f;
    glm::vec3 CameraPosition = glm::vec3(0.0f);
    glm::vec3 CameraForward = glm::vec3(0.0f);
    glm::mat4 CameraMatrix = glm::mat4(1.0f);
    glm::mat4 CameraProjection = glm::mat4(1.0f);
    glm::mat4 CameraView = glm::mat4(1.0f);
};

class Shader
{
  public:
    virtual ~Shader() = default;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    virtual void Prepare(const sShaderPrepareData& prepareData) = 0;

    virtual void SetUniform(const std::string& uniform, int value) = 0;
    virtual void SetUniform(const std::string& uniform, float value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::vec2& value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::vec3& value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::vec4& value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::mat2& value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::mat3& value) = 0;
    virtual void SetUniform(const std::string& uniform, const glm::mat4& value) = 0;

    virtual const std::string& GetName() const = 0;
};
} // namespace Lumeda