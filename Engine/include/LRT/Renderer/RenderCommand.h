#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Vec4.h"
#include "LRT/Renderer/VertexArray.h"

namespace LRT::Renderer {

    class RenderCommand {
    public:
        static void Init();
        static void SetViewport(u32 x, u32 y, u32 width, u32 height);
        static void SetClearColor(const Math::Vec4& color);
        static void Clear();
        static void DrawIndexed(const VertexArray& vao, u32 indexCount = 0);
        static void SetWireframeMode(bool enabled);
        static void SetDepthTest(bool enabled);
        static void SetBlending(bool enabled);
    };

} // namespace LRT::Renderer
