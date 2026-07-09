#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Node;

class LeafNode
{
  friend Node;

public:
  LeafNode(const tString& name) : m_Name(name), m_Parent(nullptr) {}
  virtual ~LeafNode() = default;

  ///////////////////////////////////////////
  // Parent
  ///////////////////////////////////////////
  Node* GetParent() { return m_Parent; }

  const tString& GetName() { return m_Name; }
  void SetName(const tString& name) { m_Name = name; }

protected:
  void ParentIsChanging(Node* parent) { m_Parent = parent; }

protected:
  tString m_Name;

  Node* m_Parent;
};

} // namespace Lumeda