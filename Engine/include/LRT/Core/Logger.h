#pragma once

#include "LRT/Core/Types.h"
#include <string_view>
#include <format>
#include <iostream>
#include <chrono>
#include <source_location>

namespace LRT {

    enum class LogLevel : u8 {
        Trace = 0,
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    class Logger {
    public:
        static void Init();
        static void SetLevel(LogLevel level);
        static LogLevel GetLevel();

        template<typename... Args>
        static void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
            if (level < s_Level) return;
            auto msg = std::format(fmt, std::forward<Args>(args)...);
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::floor<std::chrono::seconds>(now);
            std::cout << std::format("[{:%H:%M:%S}] [{}] {}\n",
                time, LevelToString(level), msg);
        }

        static const char* LevelToString(LogLevel level);

    private:
        static LogLevel s_Level;
    };

} // namespace LRT

#define LRT_TRACE(...) ::LRT::Logger::Log(::LRT::LogLevel::Trace, __VA_ARGS__)
#define LRT_DEBUG(...) ::LRT::Logger::Log(::LRT::LogLevel::Debug, __VA_ARGS__)
#define LRT_INFO(...)  ::LRT::Logger::Log(::LRT::LogLevel::Info, __VA_ARGS__)
#define LRT_WARN(...)  ::LRT::Logger::Log(::LRT::LogLevel::Warn, __VA_ARGS__)
#define LRT_ERROR(...) ::LRT::Logger::Log(::LRT::LogLevel::Error, __VA_ARGS__)
#define LRT_FATAL(...) ::LRT::Logger::Log(::LRT::LogLevel::Fatal, __VA_ARGS__)


