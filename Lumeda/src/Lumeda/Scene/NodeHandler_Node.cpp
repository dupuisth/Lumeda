#include <Lumeda/Resources/WorldHandler.h>
#include <Lumeda/Scene/NodeHandler_Node.h>

using namespace Lumeda;
using namespace tinyxml2;

std::unique_ptr<iLeafNodeDescription> NodeHandler::Read(XMLElement& element)
{
}

XMLElement* NodeHandler::Write(XMLDocument& document, LeafNode& node)
{
  XMLElement* nodeElement = CreateDefaultElement(document, node);

  Node& cNode = static_cast<Node&>(node);

  // Create the childs element.
  XMLElement* childsElement = document.NewElement(ChildsElementName.c_str());
  for (const auto& child : cNode.GetChilds())
  {
    XMLElement* serializedChild = nullptr;
    for (const auto& handler : m_WorldHandler.GetHandlers())
    {
      if (child->GetTypeId() == handler->GetHandlerTypeId())
      {
        serializedChild = handler->Write(document, *child);
      }
    }

    if (serializedChild == nullptr)
    {
      LUMEDA_CORE_TRACE("[NodeHandler_Node] Failed to serialize children node (type={0})", child->GetTypeId());
    }
    else
    {
      childsElement->InsertEndChild(serializedChild);
    }
  }
  nodeElement->InsertEndChild(childsElement);
  return nodeElement;
}
