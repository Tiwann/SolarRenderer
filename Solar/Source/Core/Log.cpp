#include "Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> solar::Log::sCoreLogger = spdlog::stdout_color_st("Logger");

void solar::Log::Init()
{
	sCoreLogger->set_pattern("%^[%T]: %v%$");
	sCoreLogger->set_level(spdlog::level::trace);
}