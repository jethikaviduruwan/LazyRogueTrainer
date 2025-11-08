#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Vec2.h"
#include "LRT/Math/Vec3.h"
#include "LRT/Math/Vec4.h"
#include "LRT/Math/Mat4.h"
#include "LRT/Renderer/Camera.h"
#include "LRT/Renderer/Texture2D.h"

namespace LRT::Renderer {

    struct Renderer2DStats {
        u32 DrawCalls = 0;
        u32 QuadCount = 0;
        u32 GetTotalVertexCount() const { return QuadCount * 4; }
        u32 GetTotalIndexCount() const { return QuadCount * 6; }
    };

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const Math::Vec2& position, const Math::Vec2& size,
                            const Math::Vec4& color);
        static void DrawQuad(const Math::Vec3& position, const Math::Vec2& size,
                            const Math::Vec4& color);
        static void DrawQuad(const Math::Vec2& position, const Math::Vec2& size,
                            const Shared<Texture2D>& texture, f32 tilingFactor = 1.0f,
                            const Math::Vec4& tintColor = { 1, 1, 1, 1 });
        static void DrawRotatedQuad(const Math::Vec2& position, const Math::Vec2& size,
                                    f32 rotation, const Math::Vec4& color);

        static Renderer2DStats GetStats();
        static void ResetStats();

    private:
        static void StartBatch();
        static void NextBatch();
    };

} // namespace LRT::Renderer
