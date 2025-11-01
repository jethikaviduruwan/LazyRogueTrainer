#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Renderer/Texture2D.h"

namespace LRT::Renderer {

    struct FramebufferSpec {
        u32 Width = 1280;
        u32 Height = 720;
        u32 Samples = 1;     // MSAA
        bool SwapChainTarget = false;
    };

    class Framebuffer {
    public:
        explicit Framebuffer(const FramebufferSpec& spec);
        ~Framebuffer();

        LRT_NON_COPYABLE(Framebuffer)

        void Bind() const;
        void Unbind() const;

        void Resize(u32 width, u32 height);
        void Invalidate();

        u32 GetColorAttachmentID() const { return m_ColorAttachment; }
        const FramebufferSpec& GetSpec() const { return m_Spec; }

        static Unique<Framebuffer> Create(const FramebufferSpec& spec);

    private:
        u32 m_RendererID = 0;
        u32 m_ColorAttachment = 0;
        u32 m_DepthAttachment = 0;
        FramebufferSpec m_Spec;
    };

} // namespace LRT::Renderer
