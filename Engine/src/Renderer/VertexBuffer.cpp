#include "LRT/Renderer/VertexBuffer.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    u32 ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Bool:   return 1;
            default: return 0;
        }
    }

    u32 ShaderDataTypeComponentCount(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Int:    return 1;
            case ShaderDataType::Int2:   return 2;
            case ShaderDataType::Int3:   return 3;
            case ShaderDataType::Int4:   return 4;
            case ShaderDataType::Mat3:   return 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
            default: return 0;
        }
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements) {
        CalculateOffsetsAndStride();
    }

    void BufferLayout::CalculateOffsetsAndStride() {
        u32 offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements) {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    VertexBuffer::VertexBuffer(const f32* vertices, u32 size) {
        // glGenBuffers(1, &m_RendererID);
        // glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        // glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        LRT_TRACE("VertexBuffer created ({} bytes)", size);
    }

    VertexBuffer::~VertexBuffer() {
        // glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Bind() const {
        // glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const {
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, u32 size) {
        // glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    Unique<VertexBuffer> VertexBuffer::Create(const f32* vertices, u32 size) {
        return MakeUnique<VertexBuffer>(vertices, size);
    }

    Unique<VertexBuffer> VertexBuffer::Create(u32 size) {
        return MakeUnique<VertexBuffer>(nullptr, size);
    }

} // namespace LRT::Renderer
