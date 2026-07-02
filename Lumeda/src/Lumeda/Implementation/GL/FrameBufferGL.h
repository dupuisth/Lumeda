#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/FrameBuffer.h>

namespace Lumeda
{
class FrameBufferGL : public iFrameBuffer
{
  public:
    FrameBufferGL(const tString& name, iLowLevelGraphics& lowLevelGraphics);
    virtual ~FrameBufferGL();

    void AttachTexture2D(eFrameBufferAttachment slot, iTexture& texture) override;

    ///////////////////////////////////////////
    // GL
    ///////////////////////////////////////////
    inline unsigned int GetHandle() { return m_Fbo; }

  private:
    unsigned int m_Fbo;
};
} // namespace Lumeda