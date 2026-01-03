#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>
#include <Lumeda/Renderer/Camera.h>

namespace Lumeda
{
	class CameraNode : public Node
	{
	public:
		CameraNode();
		virtual ~CameraNode();

		Camera* GetCamera();

	protected:
		void OnUpdate() override;
		void OnRenderImGui() override;

	protected:
		Camera* m_Camera;
		bool m_IsMain;
	};
}