#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GpuShader.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/GpuProgramManager.h>
#include <Lumeda/Resources/GpuShaderManager.h>
#include <Lumeda/Resources/Resources.h>
#include <Lumeda/Resources/TextureManager.h>

using namespace Lumeda;

Resources::Resources() : iUpdateable("Resources")
{
  m_Graphics = nullptr;

  m_TextureManager = nullptr;
  m_GpuProgramManager = nullptr;
}

Resources::~Resources()
{
}

void Resources::Init(Graphics& graphics)
{
  // Store the dependencies
  m_Graphics = &graphics;

  // Create the managers
  m_TextureManager = std::make_unique<TextureManager>(*this, *m_Graphics);
  m_GpuShaderManager = std::make_unique<GpuShaderManager>(*this, *m_Graphics);
  m_GpuProgramManager = std::make_unique<GpuProgramManager>(*this, *m_Graphics);
}