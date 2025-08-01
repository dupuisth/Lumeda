#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/TickVector.h>

namespace Lumeda
{
	class Scene;
	class Entity;

	class Component
	{
	public:
		Component();
		virtual ~Component();

		virtual void Update() { };
		virtual void Render() { };
		virtual void RenderImGui() { };
	};
}