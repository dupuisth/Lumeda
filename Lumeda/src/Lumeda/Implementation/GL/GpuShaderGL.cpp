#include <glad/glad.h>
#include <Lumeda/Implementation/GL/GpuShaderGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/System/LowLevelSystem.h>

using namespace Lumeda;

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

  const char* source = stringContent.c_str();
  return CreateFromSource(source);
}

bool GpuShaderGL::CreateFromSource(const char* source)
{
  GLenum GLShaderType = ShaderTypeToGLType(m_Type);

  m_Handle = glCreateShader(GLShaderType);
  glShaderSource(m_Handle, 1, &source, nullptr);
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
}