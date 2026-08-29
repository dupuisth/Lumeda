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
    DrawResources();
  }
}

void EditorStack::DrawHierarchy()
{
  ImGuiIO& io = ImGui::GetIO();

  ImGui::SetNextWindowPos(ImVec2(0, MainMenuBarHeight));
  ImGui::SetNextWindowSize(ImVec2(HierarchyWidth, io.DisplaySize.y - MainMenuBarHeight - ResourcesHeight));

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

  ImGui::Begin("Scene", nullptr, flags);

  DrawHierarchyWorker(m_World->GetRootNode());

  ImGui::End();
}

void EditorStack::DrawHierarchyWorker(LeafNode& leafnode)
{
  // Check if is a Node.
  Node* node = dynamic_cast<Node*>(&leafnode);

  ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

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

void EditorStack::DrawResources()
{
  ImGuiIO& io = ImGui::GetIO();

  ImGui::SetNextWindowPos(ImVec2(0, io.DisplaySize.y - ResourcesHeight));
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, ResourcesHeight));

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

  ImGui::Begin("Assets", nullptr, flags);

  ImGui::End();
}

void EditorStack::DrawSelected()
{

  ImGuiIO& io = ImGui::GetIO();

  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - InspectorWidth, MainMenuBarHeight));
  ImGui::SetNextWindowSize(ImVec2(InspectorWidth, io.DisplaySize.y - MainMenuBarHeight - ResourcesHeight));

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

  ImGui::Begin("Inspector", nullptr, flags);

  if (m_SelectedNode != nullptr)
  {
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
  }

  ImGui::End();
}
