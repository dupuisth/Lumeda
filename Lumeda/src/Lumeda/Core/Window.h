#pragma once

#include <Lumeda/Core/Base.h>

#include <memory>

namespace Lumeda
{
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0 ;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create();
	};
}