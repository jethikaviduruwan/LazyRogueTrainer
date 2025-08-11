#include "LRT/Memory/LinearAllocator.h"
#include "LRT/Core/Logger.h"
#include <cstring>

namespace LRT::Memory {

    LinearAllocator::LinearAllocator(u64 totalSize)
        : m_TotalSize(totalSize), m_Offset(0) {
        m_Memory = std::malloc(totalSize);
        LRT_ASSERT_MSG(m_Memory, "LinearAllocator: Failed to allocate memory");
        LRT_TRACE("LinearAllocator created: {} bytes", totalSize);
    }

    LinearAllocator::~LinearAllocator() {
        if (m_Memory) {
            std::free(m_Memory);
            m_Memory = nullptr;
        }
    }

    LinearAllocator::LinearAllocator(LinearAllocator&& other) noexcept
        : m_Memory(other.m_Memory), m_TotalSize(other.m_TotalSize), m_Offset(other.m_Offset) {
        other.m_Memory = nullptr;
        other.m_TotalSize = 0;
        other.m_Offset = 0;
    }

    LinearAllocator& LinearAllocator::operator=(LinearAllocator&& other) noexcept {
        if (this != &other) {
            std::free(m_Memory);
            m_Memory = other.m_Memory;
            m_TotalSize = other.m_TotalSize;
            m_Offset = other.m_Offset;
            other.m_Memory = nullptr;
            other.m_TotalSize = 0;
            other.m_Offset = 0;
        }
        return *this;
    }

    void* LinearAllocator::Allocate(u64 size, u64 alignment) {
        u64 currentAddr = reinterpret_cast<u64>(m_Memory) + m_Offset;
        u64 padding = 0;
        if (alignment > 0 && currentAddr % alignment != 0) {
            padding = alignment - (currentAddr % alignment);
        }

        u64 alignedOffset = m_Offset + padding;
        if (alignedOffset + size > m_TotalSize) {
            LRT_ERROR("LinearAllocator: Out of memory! Requested {} bytes, {} available",
                      size, m_TotalSize - m_Offset);
            return nullptr;
        }

        m_Offset = alignedOffset + size;
        return reinterpret_cast<void*>(reinterpret_cast<u64>(m_Memory) + alignedOffset);
    }

    void LinearAllocator::Reset() {
        m_Offset = 0;
    }

} // namespace LRT::Memory
