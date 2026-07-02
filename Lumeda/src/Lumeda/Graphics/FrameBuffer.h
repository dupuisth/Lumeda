#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>

namespace Lumeda
{
class iLowLevelGraphics;
class iTexture;

class iFrameBuffer
{
  public:
    iFrameBuffer(const tString& name, iLowLevelGraphics& lowLevelGraphics);
    virtual ~iFrameBuffer() = default;

    virtual const tString& GetName() const { return m_Name; }

    virtual void AttachTexture2D(eFrameBufferAttachment slot, iTexture& texture) = 0;

  protected:
    iLowLevelGraphics& m_LowlevelGraphics;
    tString m_Name;
};
} // namespace Lumeda