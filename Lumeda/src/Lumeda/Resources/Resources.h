#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class TextureManager;
class Graphics;

class Resources : public iUpdateable
{
public:
  Resources() : iUpdateable("Resources") {}
  ~Resources() = default;

  void Init(Graphics* graphics);

  ///////////////////////////////////////////
  // Managers getters
  ///////////////////////////////////////////
  TextureManager& GetTextureManager() { return *m_TextureManager; }
  //---------------------------------------//

private:
  Graphics* m_Graphics;

  ///////////////////////////////////////////
  // Managers
  ///////////////////////////////////////////
  std::unique_ptr<TextureManager> m_TextureManager;
  //---------------------------------------//
};
} // namespace Lumeda