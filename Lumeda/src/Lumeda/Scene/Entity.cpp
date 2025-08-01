#include <Lumeda/Scene/Entity.h>

#include <Lumeda/Scene/Scene.h>
#include <Lumeda/Scene/Component.h>

using namespace Lumeda;

Entity::Entity()
{
	LUMEDA_PROFILE;
}

Entity::~Entity()
{
	LUMEDA_PROFILE;
}

void Entity::Update()
{
	LUMEDA_PROFILE;
	AddPendingComponents();

	for (size_t i = 0; i < m_Components.Current.size(); i++)
	{
		m_Components.Current[i]->Update();
	}

	RemovePendingComponents();
}

void Entity::Render()
{
	LUMEDA_PROFILE;	
	for (size_t i = 0; i < m_Components.Current.size(); i++)
	{
		m_Components.Current[i]->Render();
	}
}

void Entity::RenderImGui()
{
	LUMEDA_PROFILE;
	for (size_t i = 0; i < m_Components.Current.size(); i++)
	{
		m_Components.Current[i]->RenderImGui();
	}
}

void Entity::AddPendingComponents()
{
	LUMEDA_PROFILE;
	// Add the pending components
	for (size_t i = 0; i < m_Components.Create.size(); i++)
	{
		m_Components.Current.push_back(m_Components.Create[i]);
	}
	m_Components.Create.clear();
}

void Entity::RemovePendingComponents()
{
	LUMEDA_PROFILE;
	// Remove the pending components
	for (size_t i = 0; i < m_Components.Destroy.size(); i++)
	{
		auto it = std::find(m_Components.Current.begin(), m_Components.Current.end(), m_Components.Destroy[i]);
		if (it != m_Components.Current.end())
		{
			m_Components.Current.erase(it);
		}
	}
	m_Components.Destroy.clear();
}
