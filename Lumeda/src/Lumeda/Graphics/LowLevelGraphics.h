#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventReceiver.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Graphics/GraphicsTypes.h>

namespace Lumeda
{
class iTexture;
class iFrameBuffer;
class iGpuProgram;
class iGpuShader;
class iVertexBuffer;
class iRenderBuffer;

class iLowLevelGraphics : public iUpdateable, public iEventReceiver
{
public:
  iLowLevelGraphics() : iUpdateable("LowLevelGraphics") {}
  virtual ~iLowLevelGraphics() = default;

  ///////////////////////////////////////////
  // Initialization
  ///////////////////////////////////////////
  virtual bool Init(int width, int height, const tString& windowTitle) = 0;

  ///////////////////////////////////////////
  // Events
  ///////////////////////////////////////////
  virtual bool OnEvent(iEvent& event) { return false; }

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
  virtual void BindFrameBuffer(iFrameBuffer& framebuffer) = 0;
  /// @brief Ensure there is a way to unbind a framebuffer without a reference to any
  virtual void UnBindFrameBuffer() = 0;
  virtual void ClearFrameBuffer(tClearFrameBufferFlag flags) = 0;
  virtual void SwapBuffers() = 0;

  virtual void SetClearColor(const tColor& color) = 0;
  virtual const tColor& GetClearColor() = 0;

  ///////////////////////////////////////////
  // RenderBuffer
  ///////////////////////////////////////////
  virtual std::unique_ptr<iRenderBuffer> CreateRenderBuffer(const tString& name) = 0;

  ///////////////////////////////////////////
  // Texture
  ///////////////////////////////////////////
  virtual std::unique_ptr<iTexture> CreateTexture(const tString& name, eTextureType type, eTextureUsage usage) = 0;
  virtual void SetTexture(unsigned int slot, iTexture& texture) = 0;
  virtual void SetActiveTextureSlot(unsigned int slot) = 0;

  ///////////////////////////////////////////
  // VertexBuffer
  ///////////////////////////////////////////
  virtual std::unique_ptr<iVertexBuffer> CreateVertexBuffer() = 0;

  ///////////////////////////////////////////
  // GpuShader
  ///////////////////////////////////////////
  virtual std::unique_ptr<iGpuShader> CreateShader(const tString& name, const twString& path, eShaderType type) = 0;

  ///////////////////////////////////////////
  // GpuProgram
  ///////////////////////////////////////////
  virtual std::unique_ptr<iGpuProgram> CreateProgram(const tString& name) = 0;

  ///////////////////////////////////////////
  // Other
  ///////////////////////////////////////////
  virtual void SetDrawMode(ePolygonFace face, ePolygonMode mode) = 0;
};
} // namespace Lumeda