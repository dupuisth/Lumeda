#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Editor/EditorNodeHandler.h>

namespace Lumeda
{
class EditorDefaultNodeHandler : public iEditorNodeHandler
{
public:
  EditorDefaultNodeHandler() = default;
  ~EditorDefaultNodeHandler() = default;

  bool SupportNodeType(LeafNode& node) override;
  void DrawNodeEditor(EditorStack& stack, LeafNode& node) override;

  LeafNode& AddToNode(EditorStack& stack, Node& parent) override;
  tString GetNodeTypeName() { return "Node"; }
};
} // namespace Lumeda