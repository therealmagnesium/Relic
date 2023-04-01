#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace Relic
{
    class Log
    {
    public:
        static void Init();

        static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
        static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
}

#define RL_CORE_TRACE(...) Relic::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define RL_CORE_INFO(...) Relic::Log::GetCoreLogger()->info(__VA_ARGS__);
#define RL_CORE_WARN(...) Relic::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define RL_CORE_ERROR(...) Relic::Log::GetCoreLogger()->error(__VA_ARGS__);
#define RL_CORE_CRITICAL(...) Relic::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define RL_TRACE(...) Relic::Log::GetClientLogger()->trace(__VA_ARGS__);
#define RL_INFO(...) Relic::Log::GetClientLogger()->info(__VA_ARGS__);
#define RL_WARN(...) Relic::Log::GetClientLogger()->warn(__VA_ARGS__);
#define RL_ERROR(...) Relic::Log::GetClientLogger()->error(__VA_ARGS__);
#define RL_CRITICAL(...) Relic::Log::GetClientLogger()->critical(__VA_ARGS__);