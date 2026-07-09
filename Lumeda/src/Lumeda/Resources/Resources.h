#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class TextureManager;
class GpuProgramManager;
class GpuShaderManager;
class Graphics;

class Resources : public iUpdateable
{
public:
  Resources();
  ~Resources();

  void Init(Graphics& graphics);

  ///////////////////////////////////////////
  // Managers getters
  ///////////////////////////////////////////
  TextureManager& GetTextureManager() { return *m_TextureManager; }
  GpuProgramManager& GetGpuProgramManager() { return *m_GpuProgramManager; }
  GpuShaderManager& GetGpuShaderManager() { return *m_GpuShaderManager; }

  //---------------------------------------//

private:
  Graphics* m_Graphics;

  ///////////////////////////////////////////
  // Managers
  ///////////////////////////////////////////
  std::unique_ptr<TextureManager> m_TextureManager;
  std::unique_ptr<GpuProgramManager> m_GpuProgramManager;
  std::unique_ptr<GpuShaderManager> m_GpuShaderManager;
  //---------------------------------------//
};
} // namespace Lumeda