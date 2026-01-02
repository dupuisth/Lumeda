#include <Lumeda/Node/ModelNode.h>
#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Model.h>
#include <Lumeda/Renderer/UniformsMap.h>
#include <imgui.h>

using namespace Lumeda;

ModelNode::ModelNode() : m_ModelName("")
{
	LUMEDA_PROFILE;
	SetName("ModelNode");
}

ModelNode::~ModelNode()
{
	LUMEDA_PROFILE;
}

void ModelNode::OnRender()
{
	LUMEDA_PROFILE;
	if (m_ModelName != "")
	{
		Renderer& renderer = Engine::Get().GetRenderer();
		Model* model = renderer.GetModel(m_ModelName);
		if (model != nullptr)
		{
			sUniformsMap uniforms;
			uniforms.Set("u_World", m_Transform.GetWorld());
			renderer.Submit(model, uniforms);
		}
		else
		{
			LUMEDA_CORE_WARN("[ModelNode] The specified m_ModelName was not found in the renderer: '{0}'", m_ModelName);
		}
	}
}

void ModelNode::SetModel(Model& model)
{
	LUMEDA_PROFILE;
	SetModel(model.GetName());
}

void ModelNode::SetModel()
{
	LUMEDA_PROFILE;
	SetModel("");
}

void ModelNode::SetModel(const std::string& modelName)
{
	LUMEDA_PROFILE;
	m_ModelName = modelName;
}

void ModelNode::OnRenderImGui()
{
	LUMEDA_PROFILE;
	Node::OnRenderImGui();

	ImGui::SeparatorText("ModelNode");
	Renderer& renderer = Engine::Get().GetRenderer();
	auto models = renderer.ListModels();
	if (ImGui::BeginCombo("Model", m_ModelName.c_str()))
	{
		for (auto& model : models)
		{
			if (ImGui::Selectable(model.first.c_str(), model.first == m_ModelName))
			{
				m_ModelName = model.first;
			}
		}

		ImGui::EndCombo();
	}
}
