#include <Lumeda/Scene/Node.h>

using namespace Lumeda;

///////////////////////////////////////////
// Transform
///////////////////////////////////////////
void Node::SetTransformDirty()
{
  m_TransformDirty = true;
  for (const auto& child : m_Childs)
  {
    child->SetTransformDirty();
  }
}

///////////////////////////////////////////
// Child nodes
///////////////////////////////////////////

LeafNode* Node::AddChild(std::unique_ptr<LeafNode> node)
{
  // Add to the childs
  LeafNode* ptr = node.get();
  m_Childs.push_back(std::move(node));
  // Set the node's parent
  ptr->ParentIsChanging(this);

  // Set the world
  ptr->SetWorld(m_World);

  return ptr;
}

std::unique_ptr<LeafNode> Node::RemoveChild(LeafNode* node)
{
  for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
  {
    if (it->get() == node)
    {
      std::unique_ptr<LeafNode> removed = std::move(*it);
      m_Childs.erase(it);
      removed->ParentIsChanging(nullptr);
      removed->SetWorld(nullptr);
      return std::move(removed);
    }
  }

  return nullptr;
}

void Node::DestroyChild(LeafNode* node)
{
  for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
  {
    if (it->get() == node)
    {
      std::unique_ptr<LeafNode> removed = std::move(*it);
      m_Childs.erase(it);
      removed->ParentIsChanging(nullptr);
      removed->SetWorld(nullptr);
      return;
    }
  }
}

void Node::HandleMessage(eUpdateableMessage message)
{
  iUpdateable::HandleMessage(message);

  for (const auto& child : m_Childs)
  {
    child->HandleMessage(message);
  }
}

void Node::SetWorld(World* world)
{
  LeafNode::SetWorld(world);

  for (const auto& child : m_Childs)
  {
    child->SetWorld(world);
  }
}