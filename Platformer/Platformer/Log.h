#ifndef LOG_H
#define LOG_H

#include <memory>
#include "spdlog/spdlog.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clientLogger;
};


#define ENGINE_LOG_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)


#define LOG_ERROR(...) ::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...) ::Log::GetClientLogger()->trace(__VA_ARGS__)


#endif // !LOG_H
