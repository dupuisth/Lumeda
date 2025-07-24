#pragma once

namespace Lumeda
{
	class Layer
	{
	public:
		virtual ~Layer() = default;


		virtual void Initialize() {};
		virtual void Terminate() {};

		virtual void Update() {};
		virtual void Render() {};
		virtual void RenderImGui() {};

	};
}