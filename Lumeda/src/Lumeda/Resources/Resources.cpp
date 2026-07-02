#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/Resources.h>
#include <Lumeda/Resources/TextureManager.h>

using namespace Lumeda;

void Resources::Init(Graphics* graphics)
{
  // Store the dependencies
  m_Graphics = graphics;

  // Create the managers
  m_TextureManager = std::make_unique<TextureManager>(*this, *m_Graphics);
}