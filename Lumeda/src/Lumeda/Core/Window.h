#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

#include <unordered_map>

namespace Lumeda
{
	class Window;
	using WindowResizeCallback = std::function<void(Window& window, int width, int height)>;
	using WindowCallbackToken = int;

	class Window
	{
	public:
		Window();
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual glm::ivec2 GetSize() const = 0;
		virtual float GetAspectRatio() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// Register the function as callback and return a token to remove the callback
		/// </summary>
		virtual WindowCallbackToken AddResizeCallback(const WindowResizeCallback& callback);
		virtual void RemoveResizeCallback(WindowCallbackToken token);

		virtual bool ShouldClose() const = 0;

		virtual void* GetNativeWindow() const = 0;


		static std::unique_ptr<Window> Create();

	protected:
		int m_NextCallbackToken;
		std::unordered_map<WindowCallbackToken, WindowResizeCallback> m_ResizeCallbacks;
	};
}