#include <Lumeda/Implementation/OpenGL/FramebufferOpenGL.h>

using namespace Lumeda;

FramebufferOpenGL::FramebufferOpenGL(const std::string& name) : m_Name(name)
{
    LUMEDA_PROFILE;
}

FramebufferOpenGL::~FramebufferOpenGL()
{
}

const std::string& FramebufferOpenGL::GetName() const
{
    LUMEDA_PROFILE;
    return m_Name;
}