#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/Mesh.h>
#include <Lumeda/Renderer/Model.h>
#include <Lumeda/Renderer/UniformsMap.h>

namespace Lumeda
{
struct sRenderCallMesh
{
    Mesh* mesh;
    Material* material;
    sUniformsMap uniformMap;
};

struct sRenderCallModel
{
    Model* model;
    sUniformsMap uniformMap;
};
} // namespace Lumeda