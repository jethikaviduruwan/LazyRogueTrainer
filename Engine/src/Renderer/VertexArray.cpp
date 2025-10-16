#include "LRT/Renderer/VertexArray.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    VertexArray::VertexArray() {
        // glGenVertexArrays(1, &m_RendererID);
        LRT_TRACE("VertexArray created");
    }

    VertexArray::~VertexArray() {
        // glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const {
        // glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const {
        // glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(Shared<VertexBuffer> vertexBuffer) {
        LRT_ASSERT_MSG(!vertexBuffer->GetLayout().GetElements().empty(),
                       "VertexBuffer has no layout");

        // glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout) {
            // glEnableVertexAttribArray(m_VertexBufferIndex);
            // glVertexAttribPointer(
            //     m_VertexBufferIndex,
            //     ShaderDataTypeComponentCount(element.Type),
            //     GL_FLOAT,
            //     element.Normalized ? GL_TRUE : GL_FALSE,
            //     layout.GetStride(),
            //     reinterpret_cast<const void*>(static_cast<u64>(element.Offset))
            // );
            m_VertexBufferIndex++;
        }

        m_VertexBuffers.push_back(std::move(vertexBuffer));
    }

    void VertexArray::SetIndexBuffer(Shared<IndexBuffer> indexBuffer) {
        // glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
        m_IndexBuffer = std::move(indexBuffer);
    }

    Unique<VertexArray> VertexArray::Create() {
        return MakeUnique<VertexArray>();
    }

} // namespace LRT::Renderer
