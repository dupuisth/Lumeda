#pragma once

#include <vector>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/LeafNode.h>

namespace Lumeda
{
class World;

class Node : public LeafNode
{
  friend World;

public:
  Node(const tString& name) : LeafNode(name) {}
  virtual ~Node() = default;

  ///////////////////////////////////////////
  // Transform
  ///////////////////////////////////////////
  void SetTransformDirty() override;

  ///////////////////////////////////////////
  // Child nodes
  ///////////////////////////////////////////
  /// @brief Add a node to the childs and returns a raw ptr to it
  LeafNode* AddChild(std::unique_ptr<LeafNode> node);
  /// @brief Remove a node from the child list and gives ownership to the caller
  std::unique_ptr<LeafNode> RemoveChild(LeafNode* node);
  /// @brief Destroy a child node (Remove a child from the child list and destroy it)
  void DestroyChild(LeafNode* node);
  const std::vector<std::unique_ptr<LeafNode>>& GetChilds() { return m_Childs; }

  void HandleMessage(eUpdateableMessage message) override;

  tString GetTypeId() const { return TypeId; }

protected:
  void SetWorld(World* world) override;

public:
  inline static const tString TypeId = "Node";

protected:
  std::vector<std::unique_ptr<LeafNode>> m_Childs;
};
} // namespace Lumeda