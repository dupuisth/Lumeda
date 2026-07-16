#pragma once

#include <GLFW/glfw3.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>

namespace Lumeda
{

class LowLevelSystemGL;
class LowLevelGraphicsGL;
class InputsGL;

struct sGLFWWindowUserData
{
  LowLevelGraphicsGL* lowLevelGraphics = nullptr;
  InputsGL* inputsGL = nullptr;
};

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
GLbitfield ClearFlagsToGLFlag(tClearFrameBufferFlag flag);
GLenum FrameBufferAttachmentToGL(eFrameBufferAttachment attachment);
GLenum PolygonFaceToGL(ePolygonFace face);
GLenum PolygonModeToGL(ePolygonMode mode);

//---------------------------------------//

class LowLevelGraphicsGL : public iLowLevelGraphics
{
public:
  LowLevelGraphicsGL(EventManager& eventManager, LowLevelSystemGL& lowLevelSystem);
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

  bool OnEvent(iEvent& event) override;
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
  // RenderBuffer
  ///////////////////////////////////////////
  std::unique_ptr<iRenderBuffer> CreateRenderBuffer(const tString& name) override;

  ///////////////////////////////////////////
  // Texture
  ///////////////////////////////////////////
  std::unique_ptr<iTexture> CreateTexture(const tString& name, eTextureType type, eTextureUsage usage) override;
  void SetTexture(unsigned int slot, iTexture& texture) override;
  void SetActiveTextureSlot(unsigned int slot) override;

  ///////////////////////////////////////////
  // VertexBuffer
  ///////////////////////////////////////////
  std::unique_ptr<iVertexBuffer> CreateVertexBuffer() override;

  ///////////////////////////////////////////
  // GpuShader
  ///////////////////////////////////////////
  std::unique_ptr<iGpuShader> CreateShader(const tString& name, const twString& path, eShaderType type) override;

  ///////////////////////////////////////////
  // GpuProgram
  ///////////////////////////////////////////
  std::unique_ptr<iGpuProgram> CreateProgram(const tString& name) override;

  ///////////////////////////////////////////
  // Other
  ///////////////////////////////////////////
  void SetDrawMode(ePolygonFace face, ePolygonMode mode) override;

  ///////////////////////////////////////////
  // GL
  ///////////////////////////////////////////
  GLFWwindow* GetOpenGLWindow() { return m_Window; }
  tString GetOpenGLShaderVersionHeader() { return "#version 460 core"; }
  sGLFWWindowUserData& GetGLFWWindowUserData() { return m_WindowUserData; }

private:
  // Events
  void OnWindowShouldClose() { m_EventManager.PushEvent(std::make_unique<WindowShouldCloseEvent>()); }
  void OnWindowResize(int width, int height) { m_EventManager.PushEvent(std::make_unique<WindowResizeEvent>(width, height)); }
  void OnWindowFrameBufferSize(int width, int height) { m_EventManager.PushEvent(std::make_unique<WindowFrameBufferSizeEvent>(width, height)); }
  void OnWindowFocus(bool focus) { m_EventManager.PushEvent(std::make_unique<WindowFocusEvent>(focus)); }
  void OnWindowPosition(int x, int y) { m_EventManager.PushEvent(std::make_unique<WindowPositionEvent>(x, y)); }

  // Static events (for GLFW callabacks)
  static void OnWindowShouldCloseCallback(GLFWwindow* window);
  static void OnWindowResizeCallback(GLFWwindow* window, int width, int height);
  static void OnWindowFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
  static void OnWindowFocusCallback(GLFWwindow* window, int focus);
  static void OnWindowPositionCallback(GLFWwindow* window, int x, int y);

  //---------------------------------------//

private:
  EventManager& m_EventManager;
  LowLevelSystemGL& m_LowLevelSystem;

  bool m_InitRan;

  tColor m_ClearColor;

  ///////////////////////////////////////////
  // GLFW Variables
  ///////////////////////////////////////////
  GLFWwindow* m_Window;
  sGLFWWindowUserData m_WindowUserData;
};

} // namespace Lumeda