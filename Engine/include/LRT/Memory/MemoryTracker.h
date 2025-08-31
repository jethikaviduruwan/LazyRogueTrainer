#pragma once

#include "LRT/Core/Types.h"
#include <string>
#include <unordered_map>
#include <mutex>

namespace LRT::Memory {

    struct AllocationRecord {
        u64 Size;
        std::string Tag;
        const char* File;
        u32 Line;
    };

    class MemoryTracker {
    public:
        static MemoryTracker& Get() {
            static MemoryTracker instance;
            return instance;
        }

        void RecordAllocation(void* ptr, u64 size, const std::string& tag,
                              const char* file = __builtin_FILE(),
                              u32 line = __builtin_LINE());
        void RecordDeallocation(void* ptr);

        [[nodiscard]] u64 GetCurrentAllocations() const { return m_CurrentCount; }
        [[nodiscard]] u64 GetTotalAllocations() const { return m_TotalCount; }
        [[nodiscard]] u64 GetCurrentBytes() const { return m_CurrentBytes; }
        [[nodiscard]] u64 GetPeakBytes() const { return m_PeakBytes; }

        void DumpLeaks() const;
        void PrintStats() const;
        void Reset();

    private:
        MemoryTracker() = default;

        mutable std::mutex m_Mutex;
        std::unordered_map<void*, AllocationRecord> m_Records;
        u64 m_CurrentCount = 0;
        u64 m_TotalCount = 0;
        u64 m_CurrentBytes = 0;
        u64 m_PeakBytes = 0;
    };

} // namespace LRT::Memory
