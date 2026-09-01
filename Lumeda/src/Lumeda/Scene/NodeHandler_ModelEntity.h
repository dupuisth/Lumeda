#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/NodeHandler.h>
#include <Lumeda/Scene/ModelEntity.h>

namespace Lumeda
{

class WorldHandler;
class ModelManager;

class ModelEntityHandler : public iNodeHandler
{
public:
  ModelEntityHandler(ModelManager& modelManager) : iNodeHandler("ModelEntityHandler"), m_ModelManager(modelManager) {}
  ~ModelEntityHandler() = default;

  tString GetHandlerTypeId() const { return ModelEntity::TypeId; }

  std::unique_ptr<iLeafNodeDescription> Read(tinyxml2::XMLElement& element) override;
  tinyxml2::XMLElement* Write(tinyxml2::XMLDocument& document, LeafNode& node) override;

private:
  ModelManager& m_ModelManager;

  inline static const tString ModelElementName = "Model";
};
} // namespace Lumeda