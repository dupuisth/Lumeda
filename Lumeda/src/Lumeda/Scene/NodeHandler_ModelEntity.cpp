#include <Lumeda/Graphics/Model.h>
#include <Lumeda/Scene/NodeHandler_ModelEntity.h>

using namespace Lumeda;
using namespace tinyxml2;

std::unique_ptr<iLeafNodeDescription> ModelEntityHandler::Read(XMLElement& element)
{
}

XMLElement* ModelEntityHandler::Write(XMLDocument& document, LeafNode& node)
{
  XMLElement* nodeElement = CreateDefaultElement(document, node);

  ModelEntity& cNode = static_cast<ModelEntity&>(node);

  XMLElement* modelElement = document.NewElement(ModelElementName.c_str());
  Model* model = cNode.GetModel();
  modelElement->SetText(model != nullptr ? model->GetName().c_str() : "");
  nodeElement->InsertEndChild(modelElement);

  return nodeElement;
}
