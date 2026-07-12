#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Renderable.h>

namespace Lumeda
{
class MeshEntity : public iRenderable
{
public:
  MeshEntity(const tString& name) : iRenderable(name) {}
  ~MeshEntity() = default;

  iVertexBuffer* GetVertexBuffer() { return m_VertexBuffer; }
  Material* GetMaterial() { return m_Material; }
  UniformMap GetAdditionalUniforms() { return iRenderable::GetAdditionalUniforms(); }

  void SetVertexBuffer(iVertexBuffer* vertexBuffer) { m_VertexBuffer = vertexBuffer; }
  void SetMaterial(Material* material) { m_Material = material; }

private:
  iVertexBuffer* m_VertexBuffer;
  Material* m_Material;
};
} // namespace Lumeda