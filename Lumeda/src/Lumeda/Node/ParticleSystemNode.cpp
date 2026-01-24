#include <Lumeda/Node/ParticleSystemNode.h>
#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Lumeda;

ParticleSystemNode::ParticleSystemNode() : m_Descriptor()
{
	LUMEDA_PROFILE;
	SetName("ParticleSystemNode");
	m_Descriptor.OriginTransform = &m_Transform;
}

ParticleSystemNode::~ParticleSystemNode()
{
	LUMEDA_PROFILE;
}

void ParticleSystemNode::OnUpdate()
{
	LUMEDA_PROFILE;
	m_Descriptor.Update();
}

void ParticleSystemNode::OnRender()
{
	LUMEDA_PROFILE;
	Engine::Get().GetRenderer().Submit(&m_Descriptor);
}

void ParticleSystemNode::OnRenderImGui()
{
	LUMEDA_PROFILE;
	Node::OnRenderImGui();

	ImGui::SeparatorText("Particle System");
	int maxParticles = m_Descriptor.GetMaxParticles();
	if (ImGui::DragInt("Max Particles", &maxParticles, 1.0f))
	{
		m_Descriptor.SetMaxParticles(maxParticles);
	}
	ImGui::DragFloat2("Velocity X Range", glm::value_ptr(m_Descriptor.InitialVelocityXRange), 0.05f);
	ImGui::DragFloat2("Velocity Y Range", glm::value_ptr(m_Descriptor.InitialVelocityYRange), 0.05f);
	ImGui::DragFloat2("Velocity Z Range", glm::value_ptr(m_Descriptor.InitialVelocityZRange), 0.05f);

	ImGui::DragFloat2("Angular Velocity Range", glm::value_ptr(m_Descriptor.InitialAngularVelocityRange), 0.1f, -100.0f, 100.0f);

	ImGui::DragFloat2("Lifetime Range", glm::value_ptr(m_Descriptor.InitialLifetimeRange), 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat2("Size Range", glm::value_ptr(m_Descriptor.InitialSizeRange), 0.1f, 0.0f, 100.0f);

	ImGui::DragFloat("Particle delay", &m_Descriptor.ParticleDelay, 0.01f, 0.0f, 100.0f);

	int activeParticle = 0;
	for (size_t i = 0; i < m_Descriptor.GetMaxParticles(); i++)
	{
		if (m_Descriptor.Particles[i].Lifetime > 0.0f) activeParticle++;
	}
	ImGui::LabelText("Active particles", "%d", activeParticle);
}

sParticleSystemDescriptor& ParticleSystemNode::GetDescriptor()
{
	LUMEDA_PROFILE;
	return m_Descriptor;
}
