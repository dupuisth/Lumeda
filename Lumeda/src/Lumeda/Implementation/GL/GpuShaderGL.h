#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GpuShader.h>

namespace Lumeda
{
class iLowLevelSystem;

class GpuShaderGL : public iGpuShader
{
public:
  GpuShaderGL(const tString& name, const twString& path, eShaderType type, iLowLevelSystem& lowLevelSystem) :
      iGpuShader(name, path, type), m_Handle(BUFFER_NULL_VALUE), m_LowLevelSystem(lowLevelSystem)
  {
  }
  ~GpuShaderGL();

  bool CreateFromFile(const twString& path) override;
  bool CreateFromSource(const char* source) override;

  ///////////////////////////////////////////
  // GL
  ///////////////////////////////////////////
  unsigned int GetOpenGLHandle() { return m_Handle; }

private:
  static const unsigned int BUFFER_NULL_VALUE = 0;
  static const size_t INFO_LOG_SIZE = 512;

  iLowLevelSystem& m_LowLevelSystem;
  unsigned int m_Handle;
};

} // namespace Lumeda