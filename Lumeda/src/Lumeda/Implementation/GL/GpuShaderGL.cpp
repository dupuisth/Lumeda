#include <glad/glad.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Implementation/GL/GpuShaderGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/System/LowLevelSystem.h>

using namespace Lumeda;

GpuShaderGL::GpuShaderGL(const tString& name,
    const twString& path,
    eShaderType type,
    iLowLevelSystem& lowLevelSystem,
    iLowLevelGraphics& lowLevelGraphics) :
    iGpuShader(name, path, type),
    m_Handle(BUFFER_NULL_VALUE),
    m_LowLevelSystem(lowLevelSystem),
    m_LowLevelGraphics(static_cast<LowLevelGraphicsGL&>(lowLevelGraphics))
{
}

GpuShaderGL::~GpuShaderGL()
{
  if (m_Handle != BUFFER_NULL_VALUE)
  {
    glDeleteShader(m_Handle);
  }
}

bool GpuShaderGL::CreateFromFile(const twString& path)
{
  tString stringContent = m_LowLevelSystem.ReadFileAsString(path);
  if (stringContent == "")
  {
    return false;
  }
  SetPath(path);

  return CreateFromSource(stringContent);
}

bool GpuShaderGL::CreateFromSource(tString& source)
{
  GLenum GLShaderType = ShaderTypeToGLType(m_Type);

  // Remove the header if present
  if (source.starts_with('#'))
  {
    size_t endPosition = source.find_first_of('\n', 0);
    source.erase(0, endPosition);
  }
  source = m_LowLevelGraphics.GetOpenGLShaderVersionHeader() + "\n" + source;

  const char* sourceC = source.c_str();

  m_Handle = glCreateShader(GLShaderType);
  glShaderSource(m_Handle, 1, &sourceC, nullptr);
  glCompileShader(m_Handle);

  // Check compilation
  int success;
  glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE)
  {
    char infoLog[INFO_LOG_SIZE];
    glGetShaderInfoLog(m_Handle, INFO_LOG_SIZE, nullptr, infoLog);
    LUMEDA_CORE_ERROR("Shader compilation failed: {0}", infoLog);
    return false;
  }

  return true;
}