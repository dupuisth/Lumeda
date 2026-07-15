#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class iGpuProgram;
class iTexture;
class iLowLevelGraphics;

#define LUMEDA_UNIFORM_MAP_DECLARATION(Type, Name) std::unordered_map<tString, Type> Name = {};
#define LUMEDA_UNIFORM_MAP_FUNCTION(Type, PassType, Name)                                                                                            \
  void SetUniform(const tString& uniform, PassType value)                                                                                            \
  {                                                                                                                                                  \
    Name[uniform] = value;                                                                                                                           \
  }

class UniformMap
{
public:
  UniformMap() {}
  ~UniformMap() = default;

  void Clear();
  void Apply(iGpuProgram& gpuProgram);

  LUMEDA_UNIFORM_MAP_FUNCTION(float, float, m_UniformFloat)
  LUMEDA_UNIFORM_MAP_FUNCTION(glm::vec2, const glm::vec2&, m_UniformVec2)
  LUMEDA_UNIFORM_MAP_FUNCTION(glm::vec3, const glm::vec3&, m_UniformVec3)
  LUMEDA_UNIFORM_MAP_FUNCTION(glm::vec4, const glm::vec4&, m_UniformVec4)
  LUMEDA_UNIFORM_MAP_FUNCTION(glm::mat3, const glm::mat3&, m_UniformMat3)
  LUMEDA_UNIFORM_MAP_FUNCTION(glm::mat4, const glm::mat4&, m_UniformMat4)
  LUMEDA_UNIFORM_MAP_FUNCTION(iTexture*, iTexture*, m_UniformTexture);

private:
  LUMEDA_UNIFORM_MAP_DECLARATION(float, m_UniformFloat)
  LUMEDA_UNIFORM_MAP_DECLARATION(glm::vec2, m_UniformVec2)
  LUMEDA_UNIFORM_MAP_DECLARATION(glm::vec3, m_UniformVec3)
  LUMEDA_UNIFORM_MAP_DECLARATION(glm::vec4, m_UniformVec4)
  LUMEDA_UNIFORM_MAP_DECLARATION(glm::mat3, m_UniformMat3)
  LUMEDA_UNIFORM_MAP_DECLARATION(glm::mat4, m_UniformMat4)
  LUMEDA_UNIFORM_MAP_DECLARATION(iTexture*, m_UniformTexture)
};

} // namespace Lumeda