#include <Lumeda/Graphics/Renderer.h>
#include <Lumeda/Scene/ModelEntity.h>

using namespace Lumeda;

void ModelEntity::CollectRenderCommands(iRenderCommandSink& sink)
{
  if (m_Model == nullptr)
  {
    return;
  }

  for (const auto& item : m_Model->GetItems())
  {
    sink.Submit({.vertexBuffer = item.vertexBuffer.get(), .material = item.material, .additionalUniforms = GetAdditionalUniforms()});
  }
}