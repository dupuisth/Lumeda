#pragma once

#include <Lumeda/Core/Base.h>

#include <Lumeda/Renderer/Mesh.h>
#include <Lumeda/Renderer/Model.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/UniformsMap.h>

namespace Lumeda
{
    struct sRenderCallMesh
    {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        sUniformsMap uniformMap;
    };

    struct sRenderCallModel
    {
        std::shared_ptr<Model> model;
        sUniformsMap uniformMap;
    };
}