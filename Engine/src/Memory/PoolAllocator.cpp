#include "LRT/Memory/PoolAllocator.h"
#include "LRT/Core/Logger.h"
#include <algorithm>

namespace LRT::Memory {

    PoolAllocator::PoolAllocator(u64 blockSize, u64 blockCount)
        : m_BlockSize(std::max(blockSize, static_cast<u64>(sizeof(FreeBlock))))
        , m_BlockCount(blockCount) {
        u64 totalSize = m_BlockSize * m_BlockCount;
        m_Memory = std::malloc(totalSize);
        LRT_ASSERT_MSG(m_Memory, "PoolAllocator: Failed to allocate memory");

        Reset();
        LRT_TRACE("PoolAllocator created: {} blocks x {} bytes = {} total",
                  m_BlockCount, m_BlockSize, totalSize);
    }

    PoolAllocator::~PoolAllocator() {
        if (m_AllocatedCount > 0) {
            LRT_WARN("PoolAllocator destroyed with {} blocks still allocated", m_AllocatedCount);
        }
        std::free(m_Memory);
    }

    void* PoolAllocator::Allocate() {
        if (!m_FreeList) {
            LRT_ERROR("PoolAllocator: No free blocks available ({} allocated)",
                      m_AllocatedCount);
            return nullptr;
        }

        FreeBlock* block = m_FreeList;
        m_FreeList = m_FreeList->Next;
        m_AllocatedCount++;
        return static_cast<void*>(block);
    }

    void PoolAllocator::Deallocate(void* ptr) {
        if (!ptr) return;

        auto* block = static_cast<FreeBlock*>(ptr);
        block->Next = m_FreeList;
        m_FreeList = block;
        m_AllocatedCount--;
    }

    void PoolAllocator::Reset() {
        m_FreeList = nullptr;
        m_AllocatedCount = 0;

        auto* start = static_cast<u8*>(m_Memory);
        for (u64 i = 0; i < m_BlockCount; ++i) {
            auto* block = reinterpret_cast<FreeBlock*>(start + i * m_BlockSize);
            block->Next = m_FreeList;
            m_FreeList = block;
        }
    }

} // namespace LRT::Memory
