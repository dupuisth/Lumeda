#include <Lumeda/Node/SpinNode.h>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Lumeda;

SpinNode::SpinNode(glm::vec3 rotationDelta) 
	: RotationDelta(rotationDelta)
{
	LUMEDA_PROFILE;
	SetName("SpinNode");
}

SpinNode::~SpinNode()
{
	LUMEDA_PROFILE;
}

void SpinNode::OnUpdate()
{
	LUMEDA_PROFILE;
	m_Transform.SetLocalRotation(m_Transform.GetLocalRotation() + RotationDelta);
}

void SpinNode::OnRenderImGui()
{
	LUMEDA_PROFILE;
	Node::OnRenderImGui();
	ImGui::SeparatorText("SpinNode");
	ImGui::DragFloat3("RotationDelta", glm::value_ptr(RotationDelta), 0.1f, -10.0f, 10.0f);
}
