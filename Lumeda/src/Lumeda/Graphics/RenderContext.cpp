#include <Lumeda/Graphics/FrameBuffer.h>
#include <Lumeda/Graphics/RenderContext.h>

using namespace Lumeda;

void RenderContext::BeginPass(iFrameBuffer* target, tClearFrameBufferFlag clearFlag)
{
  if (target == nullptr)
  {
    // Make sure no framebuffer is bind
    m_LowLevelGraphics.UnBindFrameBuffer();
  }
  else
  {
    // Else bind the given framebuffer
    m_LowLevelGraphics.BindFrameBuffer(*target);
  }

  if (clearFlag != 0)
  {
    m_LowLevelGraphics.ClearFrameBuffer(clearFlag);
  }

  // Make sure we're in sync with the actual mode
  m_LowLevelGraphics.SetDrawMode(m_Face, m_Mode);
}

void RenderContext::Draw(sRenderCommand& command, const UniformMap& globalUniforms)
{
  if (command.material == nullptr || command.vertexBuffer == nullptr)
  {
    LUMEDA_CORE_WARN("[RenderContext] material and/or vertexBuffer is nullptr");
    return;
  }

  Material& material = *command.material;
  iGpuProgram* gpuProgram = material.GetProgram();
  if (gpuProgram == nullptr)
  {
    LUMEDA_CORE_WARN("[RenderContext] gpuProgram of the material is nullptr");
    return;
  }

  // Check if the current settings match
  if (m_Face != command.face || m_Mode != command.mode)
  {
    m_Face = command.face;
    m_Mode = command.mode;
    m_LowLevelGraphics.SetDrawMode(command.face, command.mode);
  }

  gpuProgram->Bind();

  // Set the uniforms
  globalUniforms.Apply(*gpuProgram);
  material.GetUniformMap().Apply(*gpuProgram);
  command.additionalUniforms.Apply(*gpuProgram);

  // Draw the vertex
  command.vertexBuffer->Draw();

  gpuProgram->UnBind();
}

void RenderContext::EndPass(iFrameBuffer* target)
{
  // Don't need to unbind of target==nullptr since it's already done in the BeginPass.
  if (target != nullptr)
  {
    m_LowLevelGraphics.UnBindFrameBuffer();
  }
}