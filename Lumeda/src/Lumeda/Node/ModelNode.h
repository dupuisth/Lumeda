#pragma once
#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>
#include <Lumeda/Renderer/Model.h>

namespace Lumeda
{
class ModelNode : public Node
{
public:
	ModelNode();
	virtual ~ModelNode();

	void OnRender() override;
	void OnRenderImGui() override;

	void SetModel(Model& model);
	void SetModel(const std::string& modelName);
	void SetModel();

protected:
	std::string m_ModelName;
};
}