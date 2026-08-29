#include <imgui.h>
#include <Lumeda/Editor/EditorStack.h>

using namespace Lumeda;

void EditorStack::SetWorld(World* world)
{
  m_SelectedNode = nullptr;
  m_World = world;
}

void EditorStack::OnDraw()
{
  if (m_World != nullptr)
  {
    DrawHierarchy();
    DrawSelected();
  }
}

void EditorStack::DrawHierarchy()
{
  ImGuiIO& io = ImGui::GetIO();

  const float panelWidth = 280.0f;

  ImGui::SetNextWindowPos(ImVec2(0, 50));
  ImGui::SetNextWindowSize(ImVec2(panelWidth, io.DisplaySize.y - 50 * 2));

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

  ImGui::Begin("Hierarchy", nullptr, flags);

  DrawHierarchyWorker(m_World->GetRootNode());

  ImGui::End();
}

void EditorStack::DrawHierarchyWorker(LeafNode& leafnode)
{
  // Check if is a Node.
  Node* node = dynamic_cast<Node*>(&leafnode);

  ImGuiTreeNodeFlags flags = 0;

  bool selected = &leafnode == m_SelectedNode;

  if (selected)
  {
    flags |= ImGuiTreeNodeFlags_Selected;
  }
  if (node == nullptr)
  {
    flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
  }

  bool opened = ImGui::TreeNodeEx(leafnode.GetName().c_str(), flags);

  if (ImGui::IsItemClicked())
  {
    m_SelectedNode = &leafnode;
  }

  if (opened && node != nullptr)
  {
    for (const auto& child : node->GetChilds())
    {
      DrawHierarchyWorker(*child);
    }

    ImGui::TreePop();
  }
}

void EditorStack::DrawSelected()
{
  if (m_SelectedNode == nullptr)
  {
    return;
  }

  ImGuiIO& io = ImGui::GetIO();

  const float panelWidth = 400.0f;

  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - panelWidth, 50));
  ImGui::SetNextWindowSize(ImVec2(panelWidth, io.DisplaySize.y - 50 * 2));

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

  ImGui::Begin("Entity Editor", nullptr, flags);

  ImGui::SeparatorText(m_SelectedNode->GetName().c_str());

  // Dispatch to the registered handlers.
  for (const auto& handler : m_NodeHandlers)
  {
    if (handler->SupportNodeType(*m_SelectedNode))
    {
      handler->DrawNodeEditor(*this, *m_SelectedNode);
    }
  }

  // For now use a list like that (don't want to mess with dialogs for now)
  Node* node = dynamic_cast<Node*>(m_SelectedNode);
  if (node != nullptr && ImGui::CollapsingHeader("Add child"))
  {
    for (const auto& handler : m_NodeHandlers)
    {
      if (ImGui::Button(handler->GetNodeTypeName().c_str()))
      {
        m_SelectedNode = &handler->AddToNode(*this, *node);
      }
    }
  }

  ImGui::End();
}
