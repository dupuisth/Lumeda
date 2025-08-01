#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/TickVector.h>
#include <Lumeda/Renderer/Camera.h>

namespace Lumeda
{
	class Entity;
	class Component;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Instantiate(std::shared_ptr<Entity> entity, bool immediate = false);
		virtual void Destroy(std::shared_ptr<Entity> entity, bool immediate = false);

		virtual void Update();
		virtual void Render(Camera* camera);
		virtual void RenderImGui();

	protected:
		virtual void AddPendingEntities();
		virtual void RemovePendingEntities();

	protected:
		TickVector<std::shared_ptr<Entity>> m_Entities;
	};
}