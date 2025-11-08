#include "LRT/Renderer/Renderer2D.h"
#include "LRT/Renderer/VertexArray.h"
#include "LRT/Renderer/Shader.h"
#include "LRT/Renderer/RenderCommand.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    struct QuadVertex {
        Math::Vec3 Position;
        Math::Vec4 Color;
        Math::Vec2 TexCoord;
        f32 TexIndex;
        f32 TilingFactor;
    };

    struct Renderer2DData {
        static constexpr u32 MaxQuads = 20000;
        static constexpr u32 MaxVertices = MaxQuads * 4;
        static constexpr u32 MaxIndices = MaxQuads * 6;
        static constexpr u32 MaxTextureSlots = 32;

        Unique<VertexArray> QuadVertexArray;
        Unique<VertexBuffer> QuadVertexBuffer;
        Unique<Shader> FlatColorShader;
        Unique<Texture2D> WhiteTexture;

        u32 QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        Math::Vec4 QuadVertexPositions[4];
        Renderer2DStats Stats;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init() {
        // Create quad VAO, VBO, IBO
        // s_Data.QuadVertexArray = VertexArray::Create();
        // s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
        // ...set layout...

        s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVertices];

        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

        LRT_INFO("Renderer2D initialized (max {} quads per batch)", Renderer2DData::MaxQuads);
    }

    void Renderer2D::Shutdown() {
        delete[] s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBufferBase = nullptr;
        LRT_INFO("Renderer2D shut down");
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        auto viewProj = camera.GetViewProjection();
        // s_Data.FlatColorShader->Bind();
        // s_Data.FlatColorShader->SetMat4("u_ViewProjection", viewProj);
        StartBatch();
    }

    void Renderer2D::EndScene() {
        Flush();
    }

    void Renderer2D::StartBatch() {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::NextBatch() {
        Flush();
        StartBatch();
    }

    void Renderer2D::Flush() {
        if (s_Data.QuadIndexCount == 0) return;

        u32 dataSize = static_cast<u32>(
            reinterpret_cast<u8*>(s_Data.QuadVertexBufferPtr)
          - reinterpret_cast<u8*>(s_Data.QuadVertexBufferBase)
        );

        // s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
        // RenderCommand::DrawIndexed(*s_Data.QuadVertexArray, s_Data.QuadIndexCount);
        s_Data.Stats.DrawCalls++;
        (void)dataSize;
    }

    void Renderer2D::DrawQuad(const Math::Vec2& position, const Math::Vec2& size,
                               const Math::Vec4& color) {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const Math::Vec3& position, const Math::Vec2& size,
                               const Math::Vec4& color) {
        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
            NextBatch();
        }

        auto transform = Math::Mat4::Translate(position) * Math::Mat4::Scale({ size.x, size.y, 1.0f });

        constexpr Math::Vec2 texCoords[] = { {0,0}, {1,0}, {1,1}, {0,1} };
        for (u32 i = 0; i < 4; i++) {
            auto transformed = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Position = { transformed.x, transformed.y, transformed.z };
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
            s_Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const Math::Vec2& position, const Math::Vec2& size,
                               const Shared<Texture2D>& texture, f32 tilingFactor,
                               const Math::Vec4& tintColor) {
        // Similar to color quad but with texture binding
        DrawQuad({ position.x, position.y, 0.0f }, size, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const Math::Vec2& position, const Math::Vec2& size,
                                      f32 rotation, const Math::Vec4& color) {
        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
            NextBatch();
        }

        auto transform = Math::Mat4::Translate({ position.x, position.y, 0.0f })
                        * Math::Mat4::RotateZ(rotation)
                        * Math::Mat4::Scale({ size.x, size.y, 1.0f });

        constexpr Math::Vec2 texCoords[] = { {0,0}, {1,0}, {1,1}, {0,1} };
        for (u32 i = 0; i < 4; i++) {
            auto transformed = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Position = { transformed.x, transformed.y, transformed.z };
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
            s_Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;
        s_Data.Stats.QuadCount++;
    }

    Renderer2DStats Renderer2D::GetStats() { return s_Data.Stats; }

    void Renderer2D::ResetStats() {
        s_Data.Stats.DrawCalls = 0;
        s_Data.Stats.QuadCount = 0;
    }

} // namespace LRT::Renderer
