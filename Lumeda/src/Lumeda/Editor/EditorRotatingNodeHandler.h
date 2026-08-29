#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Editor/EditorNodeHandler.h>

namespace Lumeda
{
class EditorRotatingEntityHandler : public iEditorNodeHandler
{
public:
  EditorRotatingEntityHandler() = default;
  ~EditorRotatingEntityHandler() = default;

  bool SupportNodeType(LeafNode& node) override;
  void DrawNodeEditor(EditorStack& stack, LeafNode& node) override;

  LeafNode& AddToNode(EditorStack& stack, Node& parent) override;
  tString GetNodeTypeName() { return "RotatingEntity"; }
};
} // namespace Lumeda