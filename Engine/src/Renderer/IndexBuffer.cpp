#include "LRT/Renderer/IndexBuffer.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    IndexBuffer::IndexBuffer(const u32* indices, u32 count)
        : m_Count(count) {
        // glGenBuffers(1, &m_RendererID);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        LRT_TRACE("IndexBuffer created ({} indices)", count);
    }

    IndexBuffer::~IndexBuffer() {
        // glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::Bind() const {
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const {
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Unique<IndexBuffer> IndexBuffer::Create(const u32* indices, u32 count) {
        return MakeUnique<IndexBuffer>(indices, count);
    }

} // namespace LRT::Renderer


