#include <Lumeda/Node/ModelNode.h>
#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Model.h>

using namespace Lumeda;

ModelNode::ModelNode() : m_ModelName("")
{
	LUMEDA_PROFILE;
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
		std::shared_ptr<Model> model = renderer.GetModel(m_ModelName);
		if (model != nullptr)
		{
			model->Draw(m_Transform.GetWorld());
		}
		else
		{
			LUMEDA_CORE_WARN("[ModelNode] The specified m_ModelName was not found in the renderer: '{0}'", m_ModelName);
		}
	}
	LUMEDA_CORE_TRACE("[ModelNode] {0} {1} {2}", m_Transform.GetRotation().x, m_Transform.GetRotation().y, m_Transform.GetRotation().z);

}

void ModelNode::SetModel(Model& model)
{
	LUMEDA_PROFILE;
	m_ModelName = model.GetName();
}

void ModelNode::SetModel(const std::string& modelName)
{
	LUMEDA_PROFILE;
	m_ModelName = modelName;
}

void ModelNode::SetModel()
{
	LUMEDA_PROFILE;
	m_ModelName = "";
}


