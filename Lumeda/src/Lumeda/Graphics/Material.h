#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/UniformMap.h>

namespace Lumeda
{
class Material
{
public:
  Material() : m_Program(nullptr), m_UniformMap() {}
  ~Material() = default;

  void SetProgram(iGpuProgram* program) { m_Program = program; }
  iGpuProgram* GetProgram() { return m_Program; }

  UniformMap& GetUniformMap() { return m_UniformMap; }

private:
  iGpuProgram* m_Program;
  UniformMap m_UniformMap;
};

} // namespace Lumeda