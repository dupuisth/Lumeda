#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class TextureManager;
class GpuProgramManager;
class GpuShaderManager;
class MaterialManager;
class ModelManager;
class Graphics;
class iResourceLoader;

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
  MaterialManager& GetMaterialManager() { return *m_MaterialManager; }
  ModelManager& GetModelManager() { return *m_ModelManager; }
  //---------------------------------------//

  ///////////////////////////////////////////
  // Loaders
  ///////////////////////////////////////////
  void LoadAll(const twString& root, bool recursive);
  void PreLoad(const twString& path);

  /// @brief Push a loader, order is important (first pushed loaded first)
  void PushLoader(std::unique_ptr<iResourceLoader> loader);
  //---------------------------------------//

private:
  void PreLoadAllWorker(const twString& root, bool recursive);

private:
  Graphics* m_Graphics;

  ///////////////////////////////////////////
  // Managers
  ///////////////////////////////////////////
  std::unique_ptr<TextureManager> m_TextureManager;
  std::unique_ptr<GpuProgramManager> m_GpuProgramManager;
  std::unique_ptr<GpuShaderManager> m_GpuShaderManager;
  std::unique_ptr<MaterialManager> m_MaterialManager;
  std::unique_ptr<ModelManager> m_ModelManager;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Loaders
  ///////////////////////////////////////////
  std::vector<std::unique_ptr<iResourceLoader>> m_Loaders;
  //---------------------------------------//
};
} // namespace Lumeda