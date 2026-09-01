#include <Lumeda/Resources/WorldHandler.h>
#include <Lumeda/Scene/Node.h>

using namespace Lumeda;
using namespace tinyxml2;

void WorldHandler::WriteWorld(World& world, const tString& path)
{
  XMLDocument document;

  XMLElement* worldElement = document.NewElement("World");

  // Iterate the whole thing.
  XMLElement* sceneTreeElement = nullptr;
  for (const auto& handler : m_NodeHandlers)
  {
    if (handler->CanHandleType(world.GetRootNode().GetTypeId()))
    {
      sceneTreeElement = handler->Write(document, world.GetRootNode());
      break;
    }
  }
  if (sceneTreeElement == nullptr)
  {
    LUMEDA_CORE_WARN("Failed to handle the root node");
  }
  else
  {
    worldElement->InsertEndChild(sceneTreeElement);
  }
  document.InsertEndChild(worldElement);

  document.SaveFile(path.c_str());
}
