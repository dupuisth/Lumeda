#include <Lumeda/Graphics/Renderer.h>
#include <Lumeda/Scene/MeshEntity.h>

using namespace Lumeda;

void MeshEntity::CollectRenderCommands(iRenderCommandSink& sink)
{
  sink.Submit(m_VertexBuffer, m_Material, GetAdditionalUniforms());
}