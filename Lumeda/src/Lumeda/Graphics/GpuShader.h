#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class iGpuShader : public iResourceBase
{
public:
  iGpuShader(const tString& name, const twString& path, eShaderType type) : iResourceBase(name, path), m_Type(type) {}
  virtual ~iGpuShader() {}

  eShaderType GetType() { return m_Type; }

  virtual bool CreateFromFile(const twString& path) = 0;
  virtual bool CreateFromSource(const char* source) = 0;

protected:
  eShaderType m_Type;
};
} // namespace Lumeda