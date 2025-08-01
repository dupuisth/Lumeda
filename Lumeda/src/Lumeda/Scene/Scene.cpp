#include <Lumeda/Scene/Scene.h>

#include <Lumeda/Scene/Entity.h>

using namespace Lumeda;

Scene::Scene()
{
	LUMEDA_PROFILE;
}

Scene::~Scene()
{
	LUMEDA_PROFILE;
}

void Scene::Instantiate(std::shared_ptr<Entity> entity, bool immediate)
{
	LUMEDA_PROFILE;
	if (immediate)
	{
		m_Entities.Current.push_back(entity);
	}
	else
	{
		m_Entities.Create.push_back(entity);
	}
}

void Scene::Destroy(std::shared_ptr<Entity> entity, bool immediate)
{
	LUMEDA_PROFILE;
	if (immediate)
	{
		auto it = std::find(m_Entities.Current.begin(), m_Entities.Current.end(), entity);
		if (it != m_Entities.Current.end())
		{
			m_Entities.Current.erase(it);
		}
	}
	else
	{
		m_Entities.Create.push_back(entity);
	}
}

void Scene::Update()
{
	LUMEDA_PROFILE;
	AddPendingEntities();

	// Update the current entities
	for (size_t i = 0; i < m_Entities.Current.size(); i++)
	{
		m_Entities.Current[i]->Update();
	}

	RemovePendingEntities();
}

void Scene::Render(Camera* camera)
{
	LUMEDA_PROFILE;
	// Render the current entities
	for (size_t i = 0; i < m_Entities.Current.size(); i++)
	{
		m_Entities.Current[i]->Render();
	}
}

void Scene::RenderImGui()
{
	LUMEDA_PROFILE;
	// Render imgui the current entities
	for (size_t i = 0; i < m_Entities.Current.size(); i++)
	{
		m_Entities.Current[i]->RenderImGui();
	}
}

void Scene::AddPendingEntities()
{
	LUMEDA_PROFILE;
	// Add the pending entities to the scene
	for (size_t i = 0; i < m_Entities.Create.size(); i++)
	{
		m_Entities.Current.push_back(m_Entities.Create[i]);
	}
	m_Entities.Create.clear();
}

void Scene::RemovePendingEntities()
{
	LUMEDA_PROFILE;
	// Remove the pending entities
	for (size_t i = 0; i < m_Entities.Destroy.size(); i++)
	{
		auto it = std::find(m_Entities.Current.begin(), m_Entities.Current.end(), m_Entities.Destroy[i]);
		if (it != m_Entities.Current.end())
		{
			m_Entities.Current.erase(it);
		}
	}
	m_Entities.Destroy.clear();
}
