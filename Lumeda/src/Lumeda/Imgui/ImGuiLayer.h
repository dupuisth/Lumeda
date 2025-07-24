#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Layer.h>

namespace Lumeda
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		void Initialize() override;
		void Terminate() override;

		void Begin();
		void End();
	};
}