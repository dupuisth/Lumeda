#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Graphics/UniformMap.h>

using namespace Lumeda;

void UniformMap::Clear()
{
  m_UniformFloat.clear();
  m_UniformVec2.clear();
  m_UniformVec3.clear();
  m_UniformVec4.clear();
  m_UniformMat3.clear();
  m_UniformMat4.clear();
  m_UniformTexture.clear();
}

#define LUMEDA_UNIFORM_MAP_APPLY(name, gpuProgram)                                                                                                   \
  for (const auto& item : name)                                                                                                                      \
  {                                                                                                                                                  \
    gpuProgram.SetUniform(item.first, item.second);                                                                                                  \
  }

void UniformMap::Apply(iGpuProgram& gpuProgram)
{
  gpuProgram.Bind();
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformFloat, gpuProgram)
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformVec2, gpuProgram)
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformVec3, gpuProgram)
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformVec4, gpuProgram)
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformMat3, gpuProgram)
  LUMEDA_UNIFORM_MAP_APPLY(m_UniformMat4, gpuProgram)

  // Custom apply for textures
  unsigned int currentTextureSlot = 0;
  for (const auto& item : m_UniformTexture)
  {
    item.second->Bind(currentTextureSlot);
    gpuProgram.SetUniform(item.first, (int)currentTextureSlot);
  }

  gpuProgram.UnBind();
}