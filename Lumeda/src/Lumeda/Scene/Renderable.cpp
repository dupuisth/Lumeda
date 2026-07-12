#include <Lumeda/Scene/Renderable.h>

using namespace Lumeda;

UniformMap iRenderable::GetAdditionalUniforms()
{
  UniformMap map = UniformMap();

  map.SetUniform("u_World", GetWorldMatrix());
  map.SetUniform("u_Position", m_Position);

  return map;
}