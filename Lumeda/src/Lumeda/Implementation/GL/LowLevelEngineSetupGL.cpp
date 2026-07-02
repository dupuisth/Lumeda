#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>

using namespace Lumeda;

LowLevelEngineSetupGL::LowLevelEngineSetupGL()
{
    m_lowLevelGraphics = std::make_unique<LowLevelGraphicsGL>();
}

LowLevelEngineSetupGL::~LowLevelEngineSetupGL() = default;

std::unique_ptr<Graphics> LowLevelEngineSetupGL::GetGraphics()
{
    return std::make_unique<Graphics>(*m_lowLevelGraphics);
}