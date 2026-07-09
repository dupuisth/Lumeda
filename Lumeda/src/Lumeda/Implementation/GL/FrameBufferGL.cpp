#include <glad/glad.h>
#include <Lumeda/Implementation/GL/FrameBufferGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/RenderBufferGL.h>
#include <Lumeda/Implementation/GL/TextureGL.h>

using namespace Lumeda;

FrameBufferGL::FrameBufferGL(const tString& name, iLowLevelGraphics& lowLevelGraphics) : iFrameBuffer(name, lowLevelGraphics)
{
  glGenFramebuffers(1, &m_Fbo);
}

FrameBufferGL::~FrameBufferGL()
{
  glDeleteFramebuffers(1, &m_Fbo);
}

void FrameBufferGL::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
}

void FrameBufferGL::UnBind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferGL::AttachTexture2D(eFrameBufferAttachment slot, iTexture& texture)
{
  GLenum GLSlot = FrameBufferAttachmentToGL(slot);

  TextureGL& casted_texture = static_cast<TextureGL&>(texture);

  glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GLSlot, GL_TEXTURE_2D, casted_texture.GetHandleGL(), 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  m_Attachments[slot] = &casted_texture;
}

void FrameBufferGL::AttachRenderBuffer(eFrameBufferAttachment slot, iRenderBuffer& renderBuffer)
{
  GLenum GLSlot = FrameBufferAttachmentToGL(slot);

  RenderBufferGL& castedRenderBuffer = static_cast<RenderBufferGL&>(renderBuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, castedRenderBuffer.GetOpenGLHandle());
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  m_AttachmentsRenderBuffer[slot] = &castedRenderBuffer;
}