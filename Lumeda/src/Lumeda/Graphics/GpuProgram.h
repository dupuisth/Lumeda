#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class iGpuShader;

class iGpuProgram : public iResourceBase
{
public:
  iGpuProgram(const tString& name) : iResourceBase(name, _W("")), m_VertexShader(nullptr), m_FragmentShader(nullptr), m_GeometryShader(nullptr) {}
  virtual ~iGpuProgram() = default;

  virtual void AttachShader(iGpuShader* shader) = 0;
  virtual void Link() = 0;
  virtual void Bind() = 0;
  virtual void UnBind() = 0;

  virtual bool Reload() override = 0;
  virtual void Unload() override = 0;
  virtual void Destroy() override = 0;

  virtual void SetUniform(const tString& uniform, int value) = 0;
  virtual void SetUniform(const tString& uniform, float value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::vec2& value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::vec3& value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::vec4& value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::mat2& value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::mat3& value) = 0;
  virtual void SetUniform(const tString& uniform, const glm::mat4& value) = 0;

protected:
  iGpuShader* m_VertexShader;
  iGpuShader* m_FragmentShader;
  iGpuShader* m_GeometryShader;
};
} // namespace Lumeda