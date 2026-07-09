#include <Lumeda/Graphics/FrameBuffer.h>

using namespace Lumeda;

iFrameBuffer::iFrameBuffer(const tString& name, iLowLevelGraphics& lowLevelGraphics) : m_Name(name), m_LowlevelGraphics(lowLevelGraphics)
{
}