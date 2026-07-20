#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Scene/Renderable.h>

using namespace Lumeda;

UniformMap iRenderable::GetAdditionalUniforms()
{
  UniformMap map = UniformMap();

  map.SetUniform(tShaderCommonUniform_ObjectWorld, GetWorldMatrix());
  map.SetUniform(tShaderCommonUniform_ObjectPosition, m_LocalPosition);

  return map;
}