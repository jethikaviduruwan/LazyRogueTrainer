#include "LRT/Core/Logger.h"

namespace LRT {

    LogLevel Logger::s_Level = LogLevel::Trace;

    void Logger::Init() {
        s_Level = LogLevel::Trace;
        LRT_INFO("Logger initialized");
    }

    void Logger::SetLevel(LogLevel level) {
        s_Level = level;
    }

    LogLevel Logger::GetLevel() {
        return s_Level;
    }

    const char* Logger::LevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Trace: return "TRACE";
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO ";
            case LogLevel::Warn:  return "WARN ";
            case LogLevel::Error: return "ERROR";
            case LogLevel::Fatal: return "FATAL";
            default: return "?????";
        }
    }

} // namespace LRT
