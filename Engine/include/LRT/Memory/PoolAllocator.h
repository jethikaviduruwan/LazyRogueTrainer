#pragma once

#include "LRT/Core/Types.h"

namespace LRT::Memory {

    class PoolAllocator {
    public:
        PoolAllocator(u64 blockSize, u64 blockCount);
        ~PoolAllocator();

        LRT_NON_COPYABLE(PoolAllocator)

        void* Allocate();
        void Deallocate(void* ptr);
        void Reset();

        [[nodiscard]] u64 GetBlockSize() const { return m_BlockSize; }
        [[nodiscard]] u64 GetBlockCount() const { return m_BlockCount; }
        [[nodiscard]] u64 GetAllocatedCount() const { return m_AllocatedCount; }
        [[nodiscard]] u64 GetFreeCount() const { return m_BlockCount - m_AllocatedCount; }

    private:
        struct FreeBlock {
            FreeBlock* Next;
        };

        void* m_Memory = nullptr;
        FreeBlock* m_FreeList = nullptr;
        u64 m_BlockSize;
        u64 m_BlockCount;
        u64 m_AllocatedCount = 0;
    };

} // namespace LRT::Memory
