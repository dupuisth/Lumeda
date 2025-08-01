#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/TickVector.h>

#include <memory>

namespace Lumeda
{
	class Scene;
	class Component;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();
		virtual void Render();
		virtual void RenderImGui();

	protected:
		virtual void AddPendingComponents();
		virtual void RemovePendingComponents();

	protected:
		TickVector<std::shared_ptr<Component>> m_Components;
	};
}