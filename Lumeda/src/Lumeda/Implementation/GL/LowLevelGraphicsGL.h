#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EventQueue.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>

namespace Lumeda
{

///////////////////////////////////////////
// Global functions
///////////////////////////////////////////

GLenum TextureTypeToGLTarget(eTextureType type);
GLenum PixelFormatToGLFormat(ePixelFormat format);
GLenum PixelFormatToGLInternalFormat(ePixelFormat format);
GLenum WrappingToGLWrapping(eTextureWrapping wrapping);
GLenum FilteringToGLFiltering(eTextureFiltering filtering);
GLenum VertexAttribTypeToGLType(eVertexAttribType type);
GLenum ShaderTypeToGLType(eShaderType type);

//---------------------------------------//

class LowLevelGraphicsGL : public iLowLevelGraphics
{
public:
  LowLevelGraphicsGL(EventQueue& eventQueue);
  ~LowLevelGraphicsGL() override;

  ///////////////////////////////////////////
  // Initialization
  ///////////////////////////////////////////
  bool Init(int width, int height, const tString& windowTitle) override;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Lifetime
  ///////////////////////////////////////////
  void Update() override;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Window management
  ///////////////////////////////////////////
  int GetWidth() const override;
  int GetHeight() const override;

  void SetSize(const glm::ivec2& size) override;

  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  ///////////////////////////////////////////
  // FrameBuffer
  ///////////////////////////////////////////
  std::unique_ptr<iFrameBuffer> CreateFrameBuffer(const tString& name) override;
  void ClearFrameBuffer(tClearFrameBufferFlag flags) override;
  void SwapBuffers() override;

  void SetClearColor(const tColor& color) override;
  const tColor& GetClearColor() override;

  ///////////////////////////////////////////
  // Texture
  ///////////////////////////////////////////
  std::unique_ptr<iTexture> CreateTexture(const tString& name, eTextureType type, eTextureUsage usage) override;
  void SetTexture(unsigned int slot, iTexture& texture) override;
  void SetActiveTextureSlot(unsigned int slot) override;

  ///////////////////////////////////////////
  // GL
  ///////////////////////////////////////////
  GLFWwindow* GetOpenGLWindow() { return m_Window; }
  //---------------------------------------//

private:
  EventQueue& m_EventQueue;

  bool m_InitRan;

  tColor m_ClearColor;

  ///////////////////////////////////////////
  // GLFW Variables
  ///////////////////////////////////////////
  GLFWwindow* m_Window;
};

} // namespace Lumeda