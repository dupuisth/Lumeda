#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Graphics/VertexBuffer.h>

namespace Lumeda
{
/// @brief Internal for the Renderer
struct sRenderCommand
{
public:
  iVertexBuffer* vertexBuffer;
  Material* material;
  UniformMap additionalUniforms;

  ePolygonFace face = ePolygonFace_Front;
  ePolygonMode mode = ePolygonMode_Fill;
};

enum eRenderItemFeatureFlag : uint32_t
{
  eRenderItemFeatureFlag_ScreenSpace = (1 << 0)
};

/// @brief What the iRenderable will submit
struct sRenderItem
{
public:
  iVertexBuffer* vertexBuffer;
  Material* material;
  UniformMap additionalUniforms;

  uint32_t featureFlags = 0;
  bool wireframe = false;
};

class iRenderItemSink
{
public:
  virtual void Submit(const sRenderItem& renderCommand) = 0;
};

} // namespace Lumeda