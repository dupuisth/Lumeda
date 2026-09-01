#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Graphics/VertexBuffer.h>
#include <Lumeda/Scene/Renderable.h>

namespace Lumeda
{
class MeshEntity : public iRenderable
{
public:
  MeshEntity(const tString& name) : iRenderable(name), m_VertexBuffer(nullptr), m_Material(nullptr) {}
  ~MeshEntity() = default;

  iVertexBuffer* GetVertexBuffer() { return m_VertexBuffer; }
  Material* GetMaterial() { return m_Material; }
  UniformMap GetAdditionalUniforms() { return iRenderable::GetAdditionalUniforms(); }

  void SetVertexBuffer(iVertexBuffer* vertexBuffer) { m_VertexBuffer = vertexBuffer; }
  void SetMaterial(Material* material) { m_Material = material; }

  void CollectRenderCommands(iRenderItemSink& sink);

  tString GetTypeId() const { return TypeId; }

public:
  inline static const tString TypeId = "MeshEntity";

private:
  iVertexBuffer* m_VertexBuffer;
  Material* m_Material;
};
} // namespace Lumeda