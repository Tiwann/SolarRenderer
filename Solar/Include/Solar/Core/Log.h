#pragma once
#include <Config.h>
#include <spdlog/spdlog.h>

#if defined(SOLAR_DEBUG)
	#define SOLAR_LOG_TRACE(...)	solar::Log::GetLogger()->trace(__VA_ARGS__)
	#define SOLAR_LOG_INFO(...)		solar::Log::GetLogger()->info(__VA_ARGS__)
	#define SOLAR_LOG_WARN(...)		solar::Log::GetLogger()->warn(__VA_ARGS__)
	#define SOLAR_LOG_ERROR(...)	solar::Log::GetLogger()->error(__VA_ARGS__) 
#else
	#define SOLAR_LOG_TRACE(...)
	#define SOLAR_LOG_INFO(...)
	#define SOLAR_LOG_WARN(...)
	#define SOLAR_LOG_ERROR(...)
#endif

SOLAR_BEGIN
class Log
{
private:
	static std::shared_ptr<spdlog::logger> sCoreLogger;
public:
	static void Init();
	static std::shared_ptr<spdlog::logger>& GetLogger() { return sCoreLogger; }
};


SOLAR_END

