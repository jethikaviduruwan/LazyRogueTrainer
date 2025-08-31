#include "LRT/Memory/MemoryTracker.h"
#include "LRT/Core/Logger.h"

namespace LRT::Memory {

    void MemoryTracker::RecordAllocation(void* ptr, u64 size, const std::string& tag,
                                          const char* file, u32 line) {
        std::lock_guard lock(m_Mutex);
        m_Records[ptr] = { size, tag, file, line };
        m_CurrentCount++;
        m_TotalCount++;
        m_CurrentBytes += size;
        if (m_CurrentBytes > m_PeakBytes) {
            m_PeakBytes = m_CurrentBytes;
        }
    }

    void MemoryTracker::RecordDeallocation(void* ptr) {
        std::lock_guard lock(m_Mutex);
        auto it = m_Records.find(ptr);
        if (it == m_Records.end()) {
            LRT_WARN("MemoryTracker: Deallocating untracked pointer");
            return;
        }
        m_CurrentBytes -= it->second.Size;
        m_CurrentCount--;
        m_Records.erase(it);
    }

    void MemoryTracker::DumpLeaks() const {
        std::lock_guard lock(m_Mutex);
        if (m_Records.empty()) {
            LRT_INFO("MemoryTracker: No leaks detected");
            return;
        }
        LRT_WARN("MemoryTracker: {} leaks detected ({} bytes)", m_CurrentCount, m_CurrentBytes);
        for (auto& [ptr, record] : m_Records) {
            LRT_WARN("  Leak: {} bytes [{}] at {}:{}", record.Size, record.Tag, record.File, record.Line);
        }
    }

    void MemoryTracker::PrintStats() const {
        std::lock_guard lock(m_Mutex);
        LRT_INFO("Memory Stats:");
        LRT_INFO("  Current allocations: {}", m_CurrentCount);
        LRT_INFO("  Total allocations:   {}", m_TotalCount);
        LRT_INFO("  Current bytes:       {}", m_CurrentBytes);
        LRT_INFO("  Peak bytes:          {}", m_PeakBytes);
    }

    void MemoryTracker::Reset() {
        std::lock_guard lock(m_Mutex);
        m_Records.clear();
        m_CurrentCount = 0;
        m_TotalCount = 0;
        m_CurrentBytes = 0;
        m_PeakBytes = 0;
    }

} // namespace LRT::Memory
