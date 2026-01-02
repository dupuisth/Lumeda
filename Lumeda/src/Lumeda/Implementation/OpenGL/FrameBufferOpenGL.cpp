#include <Lumeda/Implementation/OpenGL/FramebufferOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#include <glad/glad.h>

using namespace Lumeda;

FramebufferOpenGL::FramebufferOpenGL(const std::string& name) : m_Name(name)
{
    LUMEDA_PROFILE;
    glGenFramebuffers(1, &m_Fbo);
}

FramebufferOpenGL::~FramebufferOpenGL()
{
    LUMEDA_PROFILE;
    glDeleteFramebuffers(1, &m_Fbo);
}

const std::string& FramebufferOpenGL::GetName() const
{
    LUMEDA_PROFILE;
    return m_Name;
}

void FramebufferOpenGL::Bind()
{
    LUMEDA_PROFILE;
    glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
}

void FramebufferOpenGL::UnBind()
{
    LUMEDA_PROFILE;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool FramebufferOpenGL::IsComplete()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        return true;
    }
    return false;
}

void FramebufferOpenGL::AttachTexture2D(eFramebufferAttachment slot, Texture2D* texture)
{
    GLenum flag;
    switch (slot)
    {
    case eFramebufferAttachment::ColorAttachment:
        flag = GL_COLOR_ATTACHMENT0;
        break;
    case eFramebufferAttachment::DepthStencilAttachment:
        flag = GL_DEPTH_STENCIL_ATTACHMENT;
        break;
    default:
        LUMEDA_CORE_WARN("[FramebufferOpenGL::AttachTexture2D] Specified slot is not recognized \'{0}\'", (int)slot);
        return;
        break;
    }

    Texture2DOpenGL* casted_texture = static_cast<Texture2DOpenGL*>(texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, flag, GL_TEXTURE_2D, casted_texture->GetOpenGLHandle(), 0);
}