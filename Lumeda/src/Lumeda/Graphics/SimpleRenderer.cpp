#include <set>
#include <Lumeda/Graphics/SimpleRenderer.h>
#include <Lumeda/Graphics/VertexBuffer.h>

using namespace Lumeda;

///////////////////////////////////////////
// Submits
///////////////////////////////////////////
void SimpleRenderer::Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms)
{
  m_RenderCommands.push_back({.vertexBuffer = vertexBuffer, .material = material, .additionalUniforms = additionalUniforms});
}

void SimpleRenderer::Submit(World& world)
{
}

///////////////////////////////////////////
// Render
///////////////////////////////////////////
void SimpleRenderer::Flush(UniformMap globalUniforms, bool clearCommands)
{
  if (m_TargetFramebuffer != nullptr)
  {
    m_TargetFramebuffer->Bind();
  }

  m_LowLevelGraphics.ClearFrameBuffer(tClearFrameBufferFlag_Color | tClearFrameBufferFlag_Depth);

  // No doubt that there is a better way of doing this, but make it work for now..
  // 1. Setup all the programs with the global uniforms
  std::set<iGpuProgram*> programs;
  for (const auto& renderCommand : m_RenderCommands)
  {
    programs.insert(renderCommand.material->GetProgram());
  }
  for (iGpuProgram* program : programs)
  {
    program->Bind();
    globalUniforms.Apply(*program);
    program->UnBind();
  }

  // 2. Apply the render commands
  for (auto& renderCommand : m_RenderCommands)
  {

    if (renderCommand.material == nullptr || renderCommand.material->GetProgram() == nullptr || renderCommand.vertexBuffer == nullptr)
    {
      LUMEDA_CORE_WARN("[SimpleRenderer] The given rendercommand is not complete");
    }

    iGpuProgram* program = renderCommand.material->GetProgram();

    program->Bind();
    renderCommand.material->GetUniformMap().Apply(*program);
    renderCommand.additionalUniforms.Apply(*program);
    renderCommand.vertexBuffer->Draw();
    program->UnBind();
  }

  if (m_TargetFramebuffer != nullptr)
  {
    m_TargetFramebuffer->UnBind();
  }
}