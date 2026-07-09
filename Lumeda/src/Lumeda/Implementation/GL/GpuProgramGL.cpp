#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <Lumeda/Implementation/GL/GpuProgramGL.h>
#include <Lumeda/Implementation/GL/GpuShaderGL.h>

using namespace Lumeda;

///////////////////////////////////////////
// Constructors
///////////////////////////////////////////
GpuProgramGL::~GpuProgramGL()
{
  if (m_Handle != BUFFER_NULL_VALUE)
  {
    glDeleteProgram(m_Handle);
  }
}

//---------------------------------------//

///////////////////////////////////////////
// Program lifetime
///////////////////////////////////////////
void GpuProgramGL::AttachShader(iGpuShader* shader)
{
  if (shader->GetType() == eShaderType_Vertex)
  {
    m_VertexShader = shader;
    m_VertexShaderCast = static_cast<GpuShaderGL*>(shader);
  }
  else if (shader->GetType() == eShaderType_Fragment)
  {
    m_FragmentShader = shader;
    m_FragmentShaderCast = static_cast<GpuShaderGL*>(shader);
  }
  else if (shader->GetType() == eShaderType_Geometry)
  {
    m_GeometryShader = shader;
    m_GeometryShaderCast = static_cast<GpuShaderGL*>(shader);
  }
  else
  {
    LUMEDA_CORE_ERROR("Unknown shader type");
  }
}

void GpuProgramGL::Link()
{
  m_Handle = glCreateProgram();

  if (m_VertexShader != nullptr)
  {
    glAttachShader(m_Handle, m_VertexShaderCast->GetOpenGLHandle());
  }
  if (m_FragmentShader != nullptr)
  {
    glAttachShader(m_Handle, m_FragmentShaderCast->GetOpenGLHandle());
  }
  if (m_GeometryShader != nullptr)
  {
    glAttachShader(m_Handle, m_GeometryShaderCast->GetOpenGLHandle());
  }

  glLinkProgram(m_Handle);

  int succes;
  glGetProgramiv(m_Handle, GL_LINK_STATUS, &succes);
  if (succes != GL_TRUE)
  {
    char infoLog[INFO_LOG_SIZE];
    glGetProgramInfoLog(m_Handle, INFO_LOG_SIZE, nullptr, infoLog);
    LUMEDA_CORE_ERROR("Failed to link program: {0}", infoLog);
    return;
  }
}

void GpuProgramGL::Bind()
{
  glUseProgram(m_Handle);
}

void GpuProgramGL::UnBind()
{
  glUseProgram(BUFFER_NULL_VALUE);
}
//---------------------------------------//

///////////////////////////////////////////
// Resource management
///////////////////////////////////////////
bool GpuProgramGL::Reload()
{
  Unload();
  Link();
  return true;
}

void GpuProgramGL::Unload()
{
  glDeleteProgram(m_Handle);
  m_Handle = BUFFER_NULL_VALUE;
}

void GpuProgramGL::Destroy()
{
  glDeleteProgram(m_Handle);
  m_Handle = BUFFER_NULL_VALUE;
}
//---------------------------------------//

///////////////////////////////////////////
// Uniforms
///////////////////////////////////////////
void GpuProgramGL::SetUniform(const tString& uniform, int value)
{
  glUniform1i(glGetUniformLocation(m_Handle, uniform.c_str()), value);
}

void GpuProgramGL::SetUniform(const tString& uniform, float value)
{
  glUniform1f(glGetUniformLocation(m_Handle, uniform.c_str()), value);
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::vec2& value)
{
  glUniform2fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::vec3& value)
{
  glUniform3fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::vec4& value)
{
  glUniform4fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::mat2& value)
{
  glUniformMatrix2fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::mat3& value)
{
  glUniformMatrix3fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GpuProgramGL::SetUniform(const tString& uniform, const glm::mat4& value)
{
  glUniformMatrix4fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
//---------------------------------------//
