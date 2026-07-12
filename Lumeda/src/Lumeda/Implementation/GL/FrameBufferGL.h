#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/FrameBuffer.h>

namespace Lumeda
{
class TextureGL;
class RenderBufferGL;

class FrameBufferGL : public iFrameBuffer
{
public:
  FrameBufferGL(const tString& name, iLowLevelGraphics& lowLevelGraphics);
  virtual ~FrameBufferGL();

  void Bind() override;
  void UnBind() override;

  void AttachTexture2D(eFrameBufferAttachment slot, iTexture& texture) override;
  void AttachRenderBuffer(eFrameBufferAttachment slot, iRenderBuffer& renderBuffer) override;

  iTexture* GetTexture2DAttachment(eFrameBufferAttachment slot) override;
  iRenderBuffer* GetRenderBufferAttachment(eFrameBufferAttachment slot) override;

  ///////////////////////////////////////////
  // GL
  ///////////////////////////////////////////
  inline unsigned int GetHandle() { return m_Fbo; }

private:
  unsigned int m_Fbo;

  TextureGL* m_Attachments[eFrameBufferAttachment_LastValue];
  RenderBufferGL* m_AttachmentsRenderBuffer[eFrameBufferAttachment_LastValue];
};
} // namespace Lumeda