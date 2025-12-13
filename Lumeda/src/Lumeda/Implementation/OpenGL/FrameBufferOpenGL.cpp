#include <Lumeda/Implementation/OpenGL/FramebufferOpenGL.h>

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

void FramebufferOpenGL::Bind()
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