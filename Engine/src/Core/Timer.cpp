#include "LRT/Core/Timer.h"
#include "LRT/Core/Logger.h"

namespace LRT {

    ScopedTimer::ScopedTimer(const std::string& name)
        : m_Name(name) {}

    ScopedTimer::~ScopedTimer() {
        f64 elapsed = m_Timer.ElapsedMillis();
        LRT_TRACE("[Timer] {} took {:.3f}ms", m_Name, elapsed);
    }

} // namespace LRT
