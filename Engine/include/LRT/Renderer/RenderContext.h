#pragma once

#include "LRT/Core/Types.h"

namespace LRT::Renderer {

    class RenderContext {
    public:
        RenderContext() = default;
        ~RenderContext();

        void Init();
        void SwapBuffers();

        [[nodiscard]] const char* GetGPUVendor() const { return m_Vendor; }
        [[nodiscard]] const char* GetGPURenderer() const { return m_RendererName; }
        [[nodiscard]] const char* GetGLVersion() const { return m_GLVersion; }

    private:
        const char* m_Vendor = "Unknown";
        const char* m_RendererName = "Unknown";
        const char* m_GLVersion = "Unknown";
        bool m_Initialized = false;
    };

} // namespace LRT::Renderer
