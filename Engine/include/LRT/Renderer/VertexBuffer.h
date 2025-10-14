#pragma once

#include "LRT/Core/Types.h"
#include <vector>
#include <string>

namespace LRT::Renderer {

    enum class ShaderDataType : u8 {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    u32 ShaderDataTypeSize(ShaderDataType type);
    u32 ShaderDataTypeComponentCount(ShaderDataType type);

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        u32 Size;
        u32 Offset;
        bool Normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)),
              Offset(0), Normalized(normalized) {}
    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements);

        const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        u32 GetStride() const { return m_Stride; }

        auto begin() const { return m_Elements.begin(); }
        auto end() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride();

        std::vector<BufferElement> m_Elements;
        u32 m_Stride = 0;
    };

    class VertexBuffer {
    public:
        VertexBuffer(const f32* vertices, u32 size);
        ~VertexBuffer();

        LRT_NON_COPYABLE(VertexBuffer)

        void Bind() const;
        void Unbind() const;

        void SetData(const void* data, u32 size);
        void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
        const BufferLayout& GetLayout() const { return m_Layout; }

        static Unique<VertexBuffer> Create(const f32* vertices, u32 size);
        static Unique<VertexBuffer> Create(u32 size); // dynamic

    private:
        u32 m_RendererID = 0;
        BufferLayout m_Layout;
    };

} // namespace LRT::Renderer
