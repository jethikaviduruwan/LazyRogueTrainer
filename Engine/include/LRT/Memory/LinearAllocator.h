#pragma once

#include "LRT/Core/Types.h"
#include <cstdlib>

namespace LRT::Memory {

    class LinearAllocator {
    public:
        explicit LinearAllocator(u64 totalSize);
        ~LinearAllocator();

        LRT_NON_COPYABLE(LinearAllocator)

        LinearAllocator(LinearAllocator&& other) noexcept;
        LinearAllocator& operator=(LinearAllocator&& other) noexcept;

        void* Allocate(u64 size, u64 alignment = alignof(std::max_align_t));
        void Reset();

        [[nodiscard]] u64 GetTotalSize() const { return m_TotalSize; }
        [[nodiscard]] u64 GetUsedSize() const { return m_Offset; }
        [[nodiscard]] u64 GetFreeSize() const { return m_TotalSize - m_Offset; }
        [[nodiscard]] f32 GetUsagePercent() const {
            return static_cast<f32>(m_Offset) / static_cast<f32>(m_TotalSize) * 100.0f;
        }

    private:
        void* m_Memory = nullptr;
        u64 m_TotalSize = 0;
        u64 m_Offset = 0;
    };

} // namespace LRT::Memory
