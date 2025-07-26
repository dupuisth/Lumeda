#include <Lumeda/Renderer/Model.h>

#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Mesh.h>

using namespace Lumeda;

Model::Model(const std::string& name) : m_Name(name), m_ModelItems()
{
	LUMEDA_PROFILE;
}

Model::~Model()
{
	LUMEDA_PROFILE;
}

void Model::Draw()
{
	LUMEDA_PROFILE;
	for (const auto& modelItem : m_ModelItems)
	{
		if (modelItem.m_Material != nullptr && modelItem.m_Mesh != nullptr)
		{
			modelItem.m_Material->Use();
			modelItem.m_Mesh->Draw();
		}
	}
}

void Model::Draw(const glm::mat4 world)
{
	LUMEDA_PROFILE;
	for (const auto& modelItem : m_ModelItems)
	{
		if (modelItem.m_Material != nullptr && modelItem.m_Mesh != nullptr)
		{
			modelItem.m_Material->SetUniform("u_World", world);
			modelItem.m_Material->Use();
			modelItem.m_Mesh->Draw();
		}
	}
}

const std::vector<ModelItem>& Model::ListItems() const
{
	LUMEDA_PROFILE;
	return m_ModelItems;
}

void Model::AttachItem(const ModelItem& modelItem)
{
	LUMEDA_PROFILE;
	m_ModelItems.push_back(modelItem);
}

void Model::SetItem(int index, const ModelItem& modelItem)
{
	LUMEDA_PROFILE;
	if (index < 0 || index > m_ModelItems.size())
	{
		LUMEDA_CORE_WARN("[Model] Index is out of bounds for SetItem");
		return;
	}
	m_ModelItems[index] = modelItem;
}

void Model::RemoveItem(int index)
{
	LUMEDA_PROFILE;
	if (index < 0 || index > m_ModelItems.size())
	{
		LUMEDA_CORE_WARN("[Model] Index is out of bounds for RemoveItem");
		return;
	}
	m_ModelItems.erase(m_ModelItems.begin() + index);
}

const std::string& Model::GetName()
{
	LUMEDA_PROFILE;
	return m_Name;
}