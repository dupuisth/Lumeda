#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Model.h>

namespace Lumeda
{
class ModelLoader
{
  public:
    static void LoadModelFromFile(Model* model, const std::string& path);
};
} // namespace Lumeda