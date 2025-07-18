#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Window.h>

#include <GLFW/glfw3.h>

namespace Lumeda
{
	namespace GLFW
	{
		class WindowGLFW : public Window
		{
		public:
			WindowGLFW();
			~WindowGLFW() override;

			void Update() override;

			int GetWidth() const override;
			int GetHeight() const override;

			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			bool ShouldClose() const override;

			void* GetNativeWindow() const override;

		private:
			GLFWwindow* m_NativeWindow;
			bool m_IsVSync;
		};
	}
}