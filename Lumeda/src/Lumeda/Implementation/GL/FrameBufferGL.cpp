#include <glad/glad.h>
#include <Lumeda/Implementation/GL/FrameBufferGL.h>
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

void FrameBufferGL::AttachTexture2D(eFrameBufferAttachment slot, iTexture& texture)
{
    LUMEDA_PROFILE;
    GLenum flag;
    switch (slot)
    {
    case eFrameBufferAttachment::eFrameBufferAttachment_Color:
        flag = GL_COLOR_ATTACHMENT0;
        break;
    case eFrameBufferAttachment::eFrameBufferAttachment_DepthStencil:
        flag = GL_DEPTH_STENCIL_ATTACHMENT;
        break;
    default:
        LUMEDA_CORE_WARN("[FrameBufferGL::AttachTexture2D] Specified slot is not recognized \'{0}\'", (int)slot);
        return;
        break;
    }

    TextureGL& casted_texture = static_cast<TextureGL&>(texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, flag, GL_TEXTURE_2D, casted_texture.GetHandleGL(), 0);
}