#pragma once

#include "LRT/Core/Types.h"

namespace LRT::Renderer {

    class IndexBuffer {
    public:
        IndexBuffer(const u32* indices, u32 count);
        ~IndexBuffer();

        LRT_NON_COPYABLE(IndexBuffer)

        void Bind() const;
        void Unbind() const;

        u32 GetCount() const { return m_Count; }

        static Unique<IndexBuffer> Create(const u32* indices, u32 count);

    private:
        u32 m_RendererID = 0;
        u32 m_Count;
    };

} // namespace LRT::Renderer
