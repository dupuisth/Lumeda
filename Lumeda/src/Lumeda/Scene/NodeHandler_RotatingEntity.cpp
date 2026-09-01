#include <Lumeda/Scene/NodeHandler_RotatingEntity.h>

using namespace Lumeda;
using namespace tinyxml2;

std::unique_ptr<iLeafNodeDescription> RotatingEntityHandler::Read(XMLElement& element)
{
}

XMLElement* RotatingEntityHandler::Write(XMLDocument& document, LeafNode& node)
{
  XMLElement* nodeElement = CreateDefaultElement(document, node);

  RotatingEntity& cNode = static_cast<RotatingEntity&>(node);

  XMLElement* rotatingElement = document.NewElement(RotatingElementName.c_str());
  rotatingElement->SetAttribute("x", cNode.GetRotating().x);
  rotatingElement->SetAttribute("y", cNode.GetRotating().y);
  rotatingElement->SetAttribute("z", cNode.GetRotating().z);

  return nodeElement;
}
