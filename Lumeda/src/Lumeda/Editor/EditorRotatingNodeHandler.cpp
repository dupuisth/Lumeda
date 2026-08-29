#include <imgui.h>
#include <Lumeda/Editor/EditorRotatingNodeHandler.h>
#include <Lumeda/Editor/EditorStack.h>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Scene/RotatingEntity.h>

using namespace Lumeda;

bool EditorRotatingEntityHandler::SupportNodeType(LeafNode& node)
{
  return dynamic_cast<RotatingEntity*>(&node) != nullptr;
}

void EditorRotatingEntityHandler::DrawNodeEditor(EditorStack& stack, LeafNode& node)
{
  if (ImGui::CollapsingHeader("RotatingEntity", ImGuiTreeNodeFlags_DefaultOpen))
  {
    ImGui::Indent(1.0f);

    // Cast
    RotatingEntity& rotatingEntity = static_cast<RotatingEntity&>(node);
    ImGui::DragFloat3("Rotation", &rotatingEntity.GetRotatingRef().x, 0.05f);

    ImGui::Unindent(1.0f);
  }
}

LeafNode& EditorRotatingEntityHandler::AddToNode(EditorStack& stack, Node& parent)
{
  std::unique_ptr<RotatingEntity> entity = std::make_unique<RotatingEntity>("RotatingEntity", stack.GetEngine().GetTimer());
  LeafNode* added = parent.AddChild(std::move(entity));
  return *added;
}
