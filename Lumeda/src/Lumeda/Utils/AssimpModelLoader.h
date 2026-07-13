#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/Model.h>
#include <Lumeda/Graphics/VertexBuffer.h>
#include <Lumeda/Resources/Resources.h>

namespace Lumeda
{

class AssimpModelLoader
{
public:
  static void Load(Model* model, const twString& path, Graphics& graphics, Resources& resources);
};

} // namespace Lumeda