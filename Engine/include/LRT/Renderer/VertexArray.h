#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Renderer/VertexBuffer.h"
#include "LRT/Renderer/IndexBuffer.h"
#include <vector>

namespace LRT::Renderer {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        LRT_NON_COPYABLE(VertexArray)

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(Shared<VertexBuffer> vertexBuffer);
        void SetIndexBuffer(Shared<IndexBuffer> indexBuffer);

        const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const Shared<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

        static Unique<VertexArray> Create();

    private:
        u32 m_RendererID = 0;
        u32 m_VertexBufferIndex = 0;
        std::vector<Shared<VertexBuffer>> m_VertexBuffers;
        Shared<IndexBuffer> m_IndexBuffer;
    };

} // namespace LRT::Renderer
