#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GpuShader.h>

namespace Lumeda
{
class iLowLevelSystem;
class iLowLevelGraphics;
class LowLevelGraphicsGL;

class GpuShaderGL : public iGpuShader
{
public:
  GpuShaderGL(const tString& name, const twString& path, eShaderType type, iLowLevelSystem& lowLevelSystem, iLowLevelGraphics& lowLevelGraphics);
  ~GpuShaderGL();

  bool Reload() { return false; }
  void Unload() {};
  void Destroy() {};

  bool CreateFromFile(const twString& path) override;
  bool CreateFromSource(tString& source) override;

  ///////////////////////////////////////////
  // GL
  ///////////////////////////////////////////
  unsigned int GetOpenGLHandle() { return m_Handle; }

private:
  static const unsigned int BUFFER_NULL_VALUE = 0;
  static const size_t INFO_LOG_SIZE = 512;

  iLowLevelSystem& m_LowLevelSystem;
  LowLevelGraphicsGL& m_LowLevelGraphics;

  unsigned int m_Handle;
};

} // namespace Lumeda