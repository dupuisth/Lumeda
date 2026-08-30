#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Editor/EditorNodeHandler.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Scene/LeafNode.h>
#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/World.h>

namespace Lumeda
{
class Engine;

class EditorStack : public iUpdateable
{
public:
  EditorStack(Engine& engine) : iUpdateable("EditorStack"), m_Engine(engine) {}

  Engine& GetEngine() { return m_Engine; }

  void OnDraw() override;

  void SetWorld(World* world);

  void PushNodeHandler(std::unique_ptr<iEditorNodeHandler> nodeHandler) { m_NodeHandlers.push_back(std::move(nodeHandler)); }

private:
  void DrawHierarchy();
  void DrawHierarchyWorker(LeafNode& leafnode);
  void DrawResources();

  void DrawSelected();

private:
  Engine& m_Engine;
  World* m_World = nullptr;
  LeafNode* m_SelectedNode = nullptr;

  std::vector<std::unique_ptr<iEditorNodeHandler>> m_NodeHandlers;

  inline static const float HierarchyWidth = 280.0f;
  inline static const float InspectorWidth = 400.0f;
  inline static const float ResourcesHeight = 200.0f;
  inline static const float MainMenuBarHeight = 23.0f;
};
} // namespace Lumeda