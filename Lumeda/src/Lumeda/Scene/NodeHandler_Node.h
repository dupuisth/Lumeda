#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/NodeHandler.h>
#include <Lumeda/Scene/Node.h>

namespace Lumeda
{

class WorldHandler;

class NodeHandler : public iNodeHandler
{
public:
  NodeHandler(WorldHandler& worldHandler) : iNodeHandler("NodeHandler"), m_WorldHandler(worldHandler) {}
  ~NodeHandler() = default;

  tString GetHandlerTypeId() const { return Node::TypeId; }

  std::unique_ptr<iLeafNodeDescription> Read(tinyxml2::XMLElement& element) override;
  tinyxml2::XMLElement* Write(tinyxml2::XMLDocument& document, LeafNode& node) override;

private:
  WorldHandler& m_WorldHandler;

  inline static const tString ChildsElementName = "Childs";
};
} // namespace Lumeda