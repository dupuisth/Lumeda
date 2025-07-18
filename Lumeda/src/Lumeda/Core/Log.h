#pragma once

#define FMT_UNICODE 0
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <memory>

namespace Lumeda
{
	/// <summary>
	/// Handles logging
	/// </summary>
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define LUMEDA_CORE_TRACE(...)    ::Lumeda::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LUMEDA_CORE_INFO(...)     ::Lumeda::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LUMEDA_CORE_WARN(...)     ::Lumeda::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LUMEDA_CORE_ERROR(...)    ::Lumeda::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LUMEDA_CORE_CRITICAL(...) ::Lumeda::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LUMEDA_TRACE(...)         ::Lumeda::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LUMEDA_INFO(...)          ::Lumeda::Log::GetClientLogger()->info(__VA_ARGS__)
#define LUMEDA_WARN(...)          ::Lumeda::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LUMEDA_ERROR(...)         ::Lumeda::Log::GetClientLogger()->error(__VA_ARGS__)
#define LUMEDA_CRITICAL(...)      ::Lumeda::Log::GetClientLogger()->critical(__VA_ARGS__)