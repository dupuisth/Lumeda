#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GpuProgram.h>

namespace Lumeda
{
class GpuShaderGL;

class GpuProgramGL : public iGpuProgram
{
public:
  GpuProgramGL(const tString& name) : iGpuProgram(name), m_Handle(BUFFER_NULL_VALUE) {}
  ~GpuProgramGL();

  void AttachShader(iGpuShader* shader) override;
  void Link() override;
  void Bind() override;
  void UnBind() override;

  bool Reload() override;
  void Unload() override;
  void Destroy() override;

  void SetUniform(const tString& uniform, int value) override;
  void SetUniform(const tString& uniform, float value) override;
  void SetUniform(const tString& uniform, const glm::vec2& value) override;
  void SetUniform(const tString& uniform, const glm::vec3& value) override;
  void SetUniform(const tString& uniform, const glm::vec4& value) override;
  void SetUniform(const tString& uniform, const glm::mat2& value) override;
  void SetUniform(const tString& uniform, const glm::mat3& value) override;
  void SetUniform(const tString& uniform, const glm::mat4& value) override;

private:
  static const unsigned int BUFFER_NULL_VALUE = 0;
  static const size_t INFO_LOG_SIZE = 512;

  GpuShaderGL* m_VertexShaderCast;
  GpuShaderGL* m_FragmentShaderCast;
  GpuShaderGL* m_GeometryShaderCast;

  unsigned int m_Handle;
};
} // namespace Lumeda