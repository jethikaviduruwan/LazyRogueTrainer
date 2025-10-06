#include "LRT/Renderer/RenderContext.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    RenderContext::~RenderContext() {
        if (m_Initialized) {
            LRT_INFO("RenderContext destroyed");
        }
    }

    void RenderContext::Init() {
        // In a real engine, this would call gladLoadGLLoader / glGetString etc.
        // m_Vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        // m_RendererName = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        // m_GLVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

        m_Initialized = true;
        LRT_INFO("RenderContext initialized");
        LRT_INFO("  GPU Vendor:   {}", m_Vendor);
        LRT_INFO("  GPU Renderer: {}", m_RendererName);
        LRT_INFO("  GL Version:   {}", m_GLVersion);
    }

    void RenderContext::SwapBuffers() {
        // glfwSwapBuffers(window);
    }

} // namespace LRT::Renderer
