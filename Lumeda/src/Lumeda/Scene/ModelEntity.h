#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Renderable.h>

namespace Lumeda
{
class Model;

class ModelEntity : public iRenderable
{
public:
  ModelEntity(const tString& name) : iRenderable(name), m_Model(nullptr) {}
  ~ModelEntity() = default;

  void CollectRenderCommands(iRenderItemSink& sink) override;

  void SetModel(Model* model) { m_Model = model; }

  UniformMap GetAdditionalUniforms() { return iRenderable::GetAdditionalUniforms(); }
  Model* GetModel() { return m_Model; }

private:
  Model* m_Model;
};
} // namespace Lumeda