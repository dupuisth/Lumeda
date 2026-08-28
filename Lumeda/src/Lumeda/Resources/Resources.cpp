#include <filesystem>
#include <iostream>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GpuShader.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/GpuProgramManager.h>
#include <Lumeda/Resources/GpuShaderManager.h>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Resources/ModelManager.h>
#include <Lumeda/Resources/ResourceLoader.h>
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
  m_MaterialManager = std::make_unique<MaterialManager>(*this, *m_Graphics);
  m_ModelManager = std::make_unique<ModelManager>(*this, *m_Graphics);
}

void Resources::LoadAll(const twString& root, bool recursive)
{
  for (const auto& entry : std::filesystem::directory_iterator(root))
  {
    // If it's a directory, explore
    if (entry.is_directory())
    {
      if (recursive)
      {
        LoadAll(entry.path().string(), recursive);
      }
      continue;
    }

    // Else, try to load it
    PreLoad(entry.path().string());
  }

  // Load everything.
  for (const auto& loader : m_Loaders)
  {
    loader->LoadPending();
  }
}

void Resources::PreLoad(const twString& path)
{
  // Get the file extension
  size_t separatorIndex = path.find_first_of('.');
  if (separatorIndex == 0 || separatorIndex == twString::npos)
  {
    return;
  }

  twString fileExtension = path.substr(separatorIndex);

  // Preload it
  for (const auto& loader : m_Loaders)
  {
    if (loader->IsExtensionSupported(fileExtension))
    {
      LUMEDA_CORE_TRACE("Sending the extension {0} to {1}", fileExtension, loader->GetName());
      loader->PreLoad(path);
      return;
    }
  }
}

void Resources::PushLoader(std::unique_ptr<iResourceLoader> loader)
{
  m_Loaders.push_back(std::move(loader));
}
