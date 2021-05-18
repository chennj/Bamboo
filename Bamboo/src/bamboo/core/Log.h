#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace BAMBOO
{
	class BAMBOO_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}
	};

}

#define BB_CORE_TRACE(...)	::BAMBOO::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define BB_CORE_ERROR(...)	::BAMBOO::Log::GetCoreLogger()->error(__VA_ARGS__);
#define BB_CORE_WARN(...)	::BAMBOO::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define BB_CORE_INFO(...)	::BAMBOO::Log::GetCoreLogger()->info(__VA_ARGS__);
#define BB_CORE_FATAL(...)	::BAMBOO::Log::GetCoreLogger()->fatal(__VA_ARGS__);
		
#define BB_TRACE(...)		::BAMBOO::Log::GetClientLogger()->trace(__VA_ARGS__);
#define BB_ERROR(...)		::BAMBOO::Log::GetClientLogger()->error(__VA_ARGS__);
#define BB_WARN(...)		::BAMBOO::Log::GetClientLogger()->warn(__VA_ARGS__);
#define BB_INFO(...)		::BAMBOO::Log::GetClientLogger()->info(__VA_ARGS__);
#define BB_FATAL(...)		::BAMBOO::Log::GetClientLogger()->fatal(__VA_ARGS__);
