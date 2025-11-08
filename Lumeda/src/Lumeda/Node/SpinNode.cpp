#include <Lumeda/Node/SpinNode.h>

using namespace Lumeda;

SpinNode::SpinNode(glm::vec3 rotationDelta) 
	: RotationDelta(rotationDelta)
{
	LUMEDA_PROFILE;
}

SpinNode::~SpinNode()
{
	LUMEDA_PROFILE;
}

void SpinNode::OnUpdate()
{
	LUMEDA_PROFILE;
	m_Transform.SetRotation(m_Transform.GetRotation() + RotationDelta);
	LUMEDA_CORE_TRACE("[SpinNode] {0} {1} {2}", m_Transform.GetRotation().x, m_Transform.GetRotation().y, m_Transform.GetRotation().z);
}
