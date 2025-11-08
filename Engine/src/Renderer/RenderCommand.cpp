#include "LRT/Renderer/RenderCommand.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    void RenderCommand::Init() {
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glEnable(GL_DEPTH_TEST);
        LRT_INFO("RenderCommand initialized");
    }

    void RenderCommand::SetViewport(u32 x, u32 y, u32 width, u32 height) {
        // glViewport(x, y, width, height);
    }

    void RenderCommand::SetClearColor(const Math::Vec4& color) {
        // glClearColor(color.x, color.y, color.z, color.w);
    }

    void RenderCommand::Clear() {
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::DrawIndexed(const VertexArray& vao, u32 indexCount) {
        u32 count = indexCount ? indexCount : vao.GetIndexBuffer()->GetCount();
        // glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        (void)count;
    }

    void RenderCommand::SetWireframeMode(bool enabled) {
        // glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
    }

    void RenderCommand::SetDepthTest(bool enabled) {
        // enabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    void RenderCommand::SetBlending(bool enabled) {
        // enabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    }

} // namespace LRT::Renderer
