#include <glad/glad.h>
#include <Lumeda/Implementation/GL/FrameBufferGL.h>
#include <Lumeda/Implementation/GL/GpuProgramGL.h>
#include <Lumeda/Implementation/GL/GpuShaderGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>
#include <Lumeda/Implementation/GL/RenderBufferGL.h>
#include <Lumeda/Implementation/GL/TextureGL.h>
#include <Lumeda/Implementation/GL/VertexBufferGL.h>

using namespace Lumeda;

LowLevelGraphicsGL::LowLevelGraphicsGL(EventManager& eventManager, LowLevelSystemGL& lowLevelSystemGL) :
    iLowLevelGraphics(), m_EventManager(eventManager), m_LowLevelSystem(lowLevelSystemGL), m_InitRan(false), m_ClearColor(0.0f)
{
}

LowLevelGraphicsGL::~LowLevelGraphicsGL()
{
  if (m_InitRan)
  {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }
}

bool LowLevelGraphicsGL::Init(int width, int height, const tString& windowTitle)
{

  ///////////////////////////////////////////
  // Initialize GLFW
  ///////////////////////////////////////////
  if (glfwInit() != GLFW_TRUE)
  {
    LUMEDA_CORE_CRITICAL("Failed to initialize GLFW");
    return false;
  }

  m_Window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
  if (m_Window == nullptr)
  {
    LUMEDA_CORE_CRITICAL("Failed to create GLFW window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_Window);

  // Set Window user pointer
  m_WindowUserData.lowLevelGraphics = this;
  glfwSetWindowUserPointer(m_Window, &m_WindowUserData);
  // Callbacks
  glfwSetWindowCloseCallback(m_Window, OnWindowShouldCloseCallback);
  glfwSetWindowSizeCallback(m_Window, OnWindowResizeCallback);
  glfwSetFramebufferSizeCallback(m_Window, OnWindowFrameBufferSizeCallback);
  glfwSetWindowFocusCallback(m_Window, OnWindowFocusCallback);
  glfwSetWindowPosCallback(m_Window, OnWindowPositionCallback);

  ///////////////////////////////////////////
  // Initialize OpenGL
  ///////////////////////////////////////////
  if (!gladLoadGL())
  {
    LUMEDA_CORE_CRITICAL("Failed to initialize glad");
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    return false;
  }

  m_InitRan = true;

  LUMEDA_CORE_INFO("[LowLevelGraphicsGL] Init");
  return true;
}

///////////////////////////////////////////
// GL Events
///////////////////////////////////////////
void LowLevelGraphicsGL::OnWindowShouldCloseCallback(GLFWwindow* window)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->lowLevelGraphics;
  lowLevelGraphicsGL->OnWindowShouldClose();
}

void LowLevelGraphicsGL::OnWindowResizeCallback(GLFWwindow* window, int width, int height)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->lowLevelGraphics;
  lowLevelGraphicsGL->OnWindowResize(width, height);
}

void LowLevelGraphicsGL::OnWindowFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->lowLevelGraphics;
  lowLevelGraphicsGL->OnWindowFrameBufferSize(width, height);
}

void LowLevelGraphicsGL::OnWindowFocusCallback(GLFWwindow* window, int focused)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->lowLevelGraphics;
  lowLevelGraphicsGL->OnWindowFocus(focused != GL_FALSE);
}

void LowLevelGraphicsGL::OnWindowPositionCallback(GLFWwindow* window, int x, int y)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->lowLevelGraphics;
  lowLevelGraphicsGL->OnWindowPosition(x, y);
}
//---------------------------------------//

///////////////////////////////////////////
// Lifetime
///////////////////////////////////////////
void LowLevelGraphicsGL::Update()
{
  glfwPollEvents();
}

bool LowLevelGraphicsGL::OnEvent(iEvent& event)
{
  if (event.GetType() == eGraphicsEvent_WindowFrameBufferSize)
  {
    // This will change later on.
    WindowFrameBufferSizeEvent& casted = static_cast<WindowFrameBufferSizeEvent&>(event);
    glViewport(0, 0, casted.Width, casted.Height);
  }

  return false;
}
//---------------------------------------//

///////////////////////////////////////////
// Window management
///////////////////////////////////////////

int LowLevelGraphicsGL::GetWidth() const
{
  int w, h;
  glfwGetWindowSize(m_Window, &w, &h);
  return w;
}

int LowLevelGraphicsGL::GetHeight() const
{
  int w, h;
  glfwGetWindowSize(m_Window, &w, &h);
  return h;
}

void LowLevelGraphicsGL::SetSize(const glm::ivec2& size)
{
}

void Lumeda::LowLevelGraphicsGL::SetVSync(bool enabled)
{
  glfwSwapInterval(enabled ? 1 : 0);
}

bool Lumeda::LowLevelGraphicsGL::IsVSync() const
{
  return false;
}

///////////////////////////////////////////
// FrameBuffer
///////////////////////////////////////////

std::unique_ptr<iFrameBuffer> LowLevelGraphicsGL::CreateFrameBuffer(const tString& name)
{
  std::unique_ptr<FrameBufferGL> framebuffer = std::make_unique<FrameBufferGL>(name, *this);
  return std::move(framebuffer);
}

void LowLevelGraphicsGL::BindFrameBuffer(iFrameBuffer& framebuffer)
{
  framebuffer.Bind();
}

void LowLevelGraphicsGL::UnBindFrameBuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LowLevelGraphicsGL::ClearFrameBuffer(tClearFrameBufferFlag flags)
{
  glClear(ClearFlagsToGLFlag(flags));
}

void LowLevelGraphicsGL::SwapBuffers()
{
  glfwSwapBuffers(m_Window);
}

void LowLevelGraphicsGL::SetClearColor(const tColor& color)
{
  glClearColor(color.x, color.y, color.z, color.w);
}

const tColor& LowLevelGraphicsGL::GetClearColor()
{
  return m_ClearColor;
}

///////////////////////////////////////////
// RenderBuffer
///////////////////////////////////////////
std::unique_ptr<iRenderBuffer> LowLevelGraphicsGL::CreateRenderBuffer(const tString& name)
{
  std::unique_ptr<RenderBufferGL> renderBuffer = std::make_unique<RenderBufferGL>(name);
  return std::move(renderBuffer);
}

///////////////////////////////////////////
// Texture
///////////////////////////////////////////

std::unique_ptr<iTexture> LowLevelGraphicsGL::CreateTexture(const tString& name, eTextureType type, eTextureUsage usage)
{
  std::unique_ptr<iTexture> texture = std::make_unique<TextureGL>(name, type, usage, *this);
  return std::move(texture);
}

void LowLevelGraphicsGL::SetTexture(unsigned int slot, iTexture& texture)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  GLenum GLType = TextureTypeToGLTarget(texture.GetType());
  glBindTexture(GLType, (static_cast<TextureGL&>(texture)).GetHandleGL());
}

void LowLevelGraphicsGL::SetActiveTextureSlot(unsigned int slot)
{
  glActiveTexture(GL_TEXTURE0 + slot);
}

///////////////////////////////////////////
// VertexBuffer
///////////////////////////////////////////
std::unique_ptr<iVertexBuffer> LowLevelGraphicsGL::CreateVertexBuffer()
{
  std::unique_ptr<iVertexBuffer> vertexBuffer = std::make_unique<VertexBufferGL>(*this);
  return std::move(vertexBuffer);
}

///////////////////////////////////////////
// GpuShader
///////////////////////////////////////////
std::unique_ptr<iGpuShader> LowLevelGraphicsGL::CreateShader(const tString& name, const twString& path, eShaderType type)
{
  std::unique_ptr<iGpuShader> shader = std::make_unique<GpuShaderGL>(name, path, type, m_LowLevelSystem, *this);
  return std::move(shader);
}

///////////////////////////////////////////
// GpuProgram
///////////////////////////////////////////
std::unique_ptr<iGpuProgram> LowLevelGraphicsGL::CreateProgram(const tString& name)
{
  std::unique_ptr<iGpuProgram> program = std::make_unique<GpuProgramGL>(name);
  return std::move(program);
}

//---------------------------------------//

///////////////////////////////////////////
// Other
///////////////////////////////////////////
void LowLevelGraphicsGL::SetDrawMode(ePolygonFace face, ePolygonMode mode)
{
  glPolygonMode(PolygonFaceToGL(face), PolygonModeToGL(mode));
}

void LowLevelGraphicsGL::EnableDepthTest(bool enable)
{
  if (enable)
  {
    glEnable(GL_DEPTH_TEST);
  }
  else
  {
    glDisable(GL_DEPTH_TEST);
  }
}
//---------------------------------------//

///////////////////////////////////////////
// Global functions
///////////////////////////////////////////

GLenum Lumeda::TextureTypeToGLTarget(eTextureType type)
{
  switch (type)
  {
  case eTextureType_2D:
    return GL_TEXTURE_2D;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::PixelFormatToGLFormat(ePixelFormat format)
{
  switch (format)
  {
  case ePixelFormat_RGB:
    return GL_RGB;
  case ePixelFormat_RGBA:
    return GL_RGBA;
  case ePixelFormat_Depth16:
    return GL_DEPTH_COMPONENT;
  case ePixelFormat_Depth24:
    return GL_DEPTH_COMPONENT;
  case ePixelFormat_Depth32:
    return GL_DEPTH_COMPONENT;
  case ePixelFormat_Depth24Stencil8:
    return GL_DEPTH_STENCIL;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::PixelFormatToGLType(ePixelFormat format)
{
  switch (format)
  {
  case ePixelFormat_RGB:
    return GL_UNSIGNED_BYTE;
  case ePixelFormat_RGBA:
    return GL_UNSIGNED_BYTE;
  case ePixelFormat_Depth24Stencil8:
    return GL_UNSIGNED_INT_24_8;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::PixelFormatToGLInternalFormat(ePixelFormat format)
{
  switch (format)
  {
  case ePixelFormat_RGB:
    return GL_RGB;
  case ePixelFormat_RGBA:
    return GL_RGBA;
  case ePixelFormat_Depth16:
    return GL_DEPTH_COMPONENT16;
  case ePixelFormat_Depth24:
    return GL_DEPTH_COMPONENT24;
  case ePixelFormat_Depth32:
    return GL_DEPTH_COMPONENT32;
  case ePixelFormat_Depth24Stencil8:
    return GL_DEPTH24_STENCIL8;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::WrappingToGLWrapping(eTextureWrapping wrapping)
{
  switch (wrapping)
  {
  case eTextureWrapping_Clamp:
    return GL_CLAMP_TO_EDGE;
  case eTextureWrapping_Repeat:
    return GL_REPEAT;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::FilteringToGLFiltering(eTextureFiltering filtering)
{
  switch (filtering)
  {
  case eTextureFiltering_Linear:
    return GL_LINEAR;
  case eTextureFiltering_Nearest:
    return GL_NEAREST;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::VertexAttribTypeToGLType(eVertexAttribType type)
{
  switch (type)
  {
  case eVertexAttribType_Float:
    return GL_FLOAT;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::ShaderTypeToGLType(eShaderType type)
{
  switch (type)
  {
  case eShaderType_Vertex:
    return GL_VERTEX_SHADER;
  case eShaderType_Fragment:
    return GL_FRAGMENT_SHADER;
  case eShaderType_Geometry:
    return GL_GEOMETRY_SHADER;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLbitfield Lumeda::ClearFlagsToGLFlag(tClearFrameBufferFlag flag)
{
  GLbitfield result = 0;

  if (flag & tClearFrameBufferFlag_Color)
  {
    result |= GL_COLOR_BUFFER_BIT;
  }
  if (flag & tClearFrameBufferFlag_Depth)
  {
    result |= GL_DEPTH_BUFFER_BIT;
  }
  if (flag & tClearFrameBufferFlag_Stencil)
  {
    result |= GL_STENCIL_BUFFER_BIT;
  }
  return result;
}

GLenum Lumeda::FrameBufferAttachmentToGL(eFrameBufferAttachment attachment)
{
  switch (attachment)
  {
  case eFrameBufferAttachment::eFrameBufferAttachment_Color:
    return GL_COLOR_ATTACHMENT0;
  case eFrameBufferAttachment::eFrameBufferAttachment_DepthStencil:
    return GL_DEPTH_STENCIL_ATTACHMENT;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::PolygonFaceToGL(ePolygonFace face)
{
  switch (face)
  {
  case ePolygonFace_Front:
    return GL_FRONT;
  case ePolygonFace_Back:
    return GL_BACK;
  case ePolygonFace_FrontBack:
    return GL_FRONT_AND_BACK;
  }
  LUMEDA_ASSERT(false);
  return 0;
}

GLenum Lumeda::PolygonModeToGL(ePolygonMode mode)
{
  switch (mode)
  {
  case ePolygonMode_Fill:
    return GL_FILL;
  case ePolygonMode_Line:
    return GL_LINE;
  case ePolygonMode_Point:
    return GL_POINT;
  }
  LUMEDA_ASSERT(false);
  return 0;
}