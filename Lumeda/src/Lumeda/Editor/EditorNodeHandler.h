#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/LeafNode.h>

namespace Lumeda
{

class EditorStack;

class iEditorNodeHandler
{
public:
  virtual ~iEditorNodeHandler() = default;

  virtual bool SupportNodeType(LeafNode& node) = 0;
  virtual void DrawNodeEditor(EditorStack& stack, LeafNode& node) = 0;

  virtual LeafNode& AddToNode(EditorStack& stack, Node& parent) = 0;
  virtual tString GetNodeTypeName() = 0;
};
} // namespace Lumeda