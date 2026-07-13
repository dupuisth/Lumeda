#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class Material : public iResourceBase
{
public:
  Material(const tString& name, const twString& path) : iResourceBase(name, path), m_Program(nullptr), m_UniformMap() {}
  ~Material() = default;

  ///////////////////////////////////////////
  // Lifetime
  ///////////////////////////////////////////
  bool Reload() { return false; }
  void Unload() {}
  void Destroy() {}

  void SetProgram(iGpuProgram* program) { m_Program = program; }
  iGpuProgram* GetProgram() { return m_Program; }

  UniformMap& GetUniformMap() { return m_UniformMap; }

private:
  iGpuProgram* m_Program;
  UniformMap m_UniformMap;
};

} // namespace Lumeda