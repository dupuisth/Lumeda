#include <imgui.h>
#include <Lumeda/Editor/EditorDefaultNodeHandler.h>
#include <Lumeda/Editor/EditorStack.h>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Scene/RotatingEntity.h>

using namespace Lumeda;

bool EditorDefaultNodeHandler::SupportNodeType(LeafNode& node)
{
  return true;
}

void EditorDefaultNodeHandler::DrawNodeEditor(EditorStack& stack, LeafNode& node)
{
  if (ImGui::CollapsingHeader("Transform"))
  {
    ImGui::Indent(1.0f);
    glm::vec3 dummyVec3 = node.GetLocalPosition();
    if (ImGui::DragFloat3("Local Position", &dummyVec3[0], 0.01f))
    {
      node.SetLocalPosition(dummyVec3);
    }

    dummyVec3 = glm::degrees(glm::eulerAngles(node.GetLocalRotation()));
    if (ImGui::DragFloat3("Local Rotation", &dummyVec3[0], 0.01f))
    {
      node.SetLocalRotationEuler(dummyVec3);
    }

    dummyVec3 = node.GetLocalScale();
    if (ImGui::DragFloat3("Local Scale", &dummyVec3[0], 0.01f))
    {
      node.SetLocalScale(dummyVec3);
    }

    ImGui::Unindent(1.0f);
  }
}

LeafNode& EditorDefaultNodeHandler::AddToNode(EditorStack& stack, Node& parent)
{
  // Never add a simple LeafNode since it should never be added as such.
  std::unique_ptr<Node> entity = std::make_unique<Node>("Node");
  LeafNode* added = parent.AddChild(std::move(entity));
  return *added;
}
