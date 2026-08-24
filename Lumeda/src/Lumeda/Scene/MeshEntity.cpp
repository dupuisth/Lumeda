#include <Lumeda/Graphics/Renderer.h>
#include <Lumeda/Scene/MeshEntity.h>

using namespace Lumeda;

void MeshEntity::CollectRenderCommands(iRenderCommandSink& sink)
{
  sink.Submit({.vertexBuffer = m_VertexBuffer, .material = m_Material, .additionalUniforms = GetAdditionalUniforms()});
}