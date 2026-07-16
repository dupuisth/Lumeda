#include <glad/glad.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/RenderBufferGL.h>

using namespace Lumeda;

RenderBufferGL::RenderBufferGL(const tString& name) : iRenderBuffer(name), m_Rbo(0)
{
  glGenRenderbuffers(1, &m_Rbo);
}

RenderBufferGL::~RenderBufferGL()
{
  glDeleteRenderbuffers(1, &m_Rbo);
}

void RenderBufferGL::Bind()
{
  glBindRenderbuffer(GL_RENDERBUFFER, m_Rbo);
}

void RenderBufferGL::UnBind()
{
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBufferGL::SetStorage(const glm::vec2& size, ePixelFormat format)
{
  glBindRenderbuffer(GL_RENDERBUFFER, m_Rbo);
  GLenum GLInternalFormat = PixelFormatToGLInternalFormat(format);
  glRenderbufferStorage(GL_RENDERBUFFER, GLInternalFormat, size.x, size.y);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}