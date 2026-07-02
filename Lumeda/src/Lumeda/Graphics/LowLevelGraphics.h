#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>

namespace Lumeda
{
class iTexture;
class iFrameBuffer;
class iLowLevelGraphics
{
  public:
    virtual ~iLowLevelGraphics() {}

    ///////////////////////////////////////////
    // Initialization
    ///////////////////////////////////////////
    virtual bool Init(int width, int height, const tString& windowTitle) = 0;

    ///////////////////////////////////////////
    // Window management
    ///////////////////////////////////////////
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    virtual void SetSize(const glm::ivec2& size) = 0;

    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    ///////////////////////////////////////////
    // FrameBuffer
    ///////////////////////////////////////////
    virtual std::unique_ptr<iFrameBuffer> CreateFrameBuffer(const tString& name) = 0;
    virtual void ClearFrameBuffer(tClearFrameBufferFlag flags) = 0;
    virtual void SwapBuffers() = 0;

    virtual void SetClearColor(const tColor& color) = 0;
    virtual const tColor& GetClearColor() = 0;

    ///////////////////////////////////////////
    // Texture
    ///////////////////////////////////////////
    virtual std::unique_ptr<iTexture> CreateTexture(const tString& name, eTextureType type, eTextureUsage usage) = 0;
    virtual void SetTexture(unsigned int slot, iTexture& texture) = 0;
    virtual void SetActiveTextureSlot(unsigned int slot) = 0;
};
} // namespace Lumeda