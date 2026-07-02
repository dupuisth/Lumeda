#include <Lumeda/Implementation/GL/FrameBufferGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/TextureGL.h>

using namespace Lumeda;

LowLevelGraphicsGL::LowLevelGraphicsGL(EventQueue& eventQueue) : iLowLevelGraphics(), m_EventQueue(eventQueue), m_InitRan(false), m_ClearColor(0.0f)
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

  // Callbacks
  glfwSetWindowUserPointer(m_Window, this);
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
  return true;
}

///////////////////////////////////////////
// GL Events
///////////////////////////////////////////
void LowLevelGraphicsGL::OnWindowShouldCloseCallback(GLFWwindow* window)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<LowLevelGraphicsGL*>(glfwGetWindowUserPointer(window));
  lowLevelGraphicsGL->OnWindowShouldClose();
}

void LowLevelGraphicsGL::OnWindowResizeCallback(GLFWwindow* window, int width, int height)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<LowLevelGraphicsGL*>(glfwGetWindowUserPointer(window));
  lowLevelGraphicsGL->OnWindowResize(width, height);
}

void LowLevelGraphicsGL::OnWindowFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<LowLevelGraphicsGL*>(glfwGetWindowUserPointer(window));
  lowLevelGraphicsGL->OnWindowFrameBufferSize(width, height);
}

void LowLevelGraphicsGL::OnWindowFocusCallback(GLFWwindow* window, int focused)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<LowLevelGraphicsGL*>(glfwGetWindowUserPointer(window));
  lowLevelGraphicsGL->OnWindowFocus(focused != GL_FALSE);
}

void LowLevelGraphicsGL::OnWindowPositionCallback(GLFWwindow* window, int x, int y)
{
  LowLevelGraphicsGL* lowLevelGraphicsGL = static_cast<LowLevelGraphicsGL*>(glfwGetWindowUserPointer(window));
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
//---------------------------------------//

///////////////////////////////////////////
// Window management
///////////////////////////////////////////

int LowLevelGraphicsGL::GetWidth() const
{
  return 0;
}

int LowLevelGraphicsGL::GetHeight() const
{
  return 0;
}

void LowLevelGraphicsGL::SetSize(const glm::ivec2& size)
{
}

void Lumeda::LowLevelGraphicsGL::SetVSync(bool enabled)
{
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
  return nullptr;
}

void LowLevelGraphicsGL::ClearFrameBuffer(tClearFrameBufferFlag flags)
{
}

void LowLevelGraphicsGL::SwapBuffers()
{
}

void LowLevelGraphicsGL::SetClearColor(const tColor& color)
{
}

const tColor& LowLevelGraphicsGL::GetClearColor()
{
  // TODO: insert return statement here
  return m_ClearColor;
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
}

void LowLevelGraphicsGL::SetActiveTextureSlot(unsigned int slot)
{
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