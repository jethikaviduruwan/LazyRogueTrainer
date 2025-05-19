#pragma once

#include "LRT/Core/Types.h"
#include <chrono>
#include <string>

namespace LRT {

    class Timer {
    public:
        Timer() { Reset(); }

        void Reset() {
            m_Start = std::chrono::high_resolution_clock::now();
        }

        f64 Elapsed() const {
            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<f64>(now - m_Start).count();
        }

        f64 ElapsedMillis() const {
            return Elapsed() * 1000.0;
        }

    private:
        std::chrono::high_resolution_clock::time_point m_Start;
    };

    class ScopedTimer {
    public:
        explicit ScopedTimer(const std::string& name);
        ~ScopedTimer();

        LRT_NON_COPYABLE(ScopedTimer)
        LRT_NON_MOVABLE(ScopedTimer)

    private:
        std::string m_Name;
        Timer m_Timer;
    };

} // namespace LRT
