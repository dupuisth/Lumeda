#include <Lumeda/Resources/NodeHandler.h>

using namespace Lumeda;
using namespace tinyxml2;

XMLElement* iNodeHandler::CreateDefaultElement(XMLDocument& document, LeafNode& node)
{
  // Create the main element
  XMLElement* nodeElement = document.NewElement(GetHandlerTypeId().c_str());

  // Write the Name Attribute
  nodeElement->SetAttribute(NameAttributeName.c_str(), node.GetName().c_str());

  // Write the Position element
  XMLElement* positionElement = document.NewElement(LocalPositionElementName.c_str());
  positionElement->SetAttribute("x", node.GetLocalPosition().x);
  positionElement->SetAttribute("y", node.GetLocalPosition().y);
  positionElement->SetAttribute("z", node.GetLocalPosition().z);
  nodeElement->InsertEndChild(positionElement);

  // Write the Rotation element
  XMLElement* rotationElement = document.NewElement(LocalRotationElementName.c_str());
  rotationElement->SetAttribute("x", node.GetLocalRotation().x);
  rotationElement->SetAttribute("y", node.GetLocalRotation().y);
  rotationElement->SetAttribute("z", node.GetLocalRotation().z);
  rotationElement->SetAttribute("w", node.GetLocalRotation().w);
  nodeElement->InsertEndChild(rotationElement);

  // Write the Scale element
  XMLElement* scaleElement = document.NewElement(LocalScaleElementName.c_str());
  scaleElement->SetAttribute("x", node.GetLocalScale().x);
  scaleElement->SetAttribute("y", node.GetLocalScale().y);
  scaleElement->SetAttribute("z", node.GetLocalScale().z);
  nodeElement->InsertEndChild(scaleElement);

  return nodeElement;
}