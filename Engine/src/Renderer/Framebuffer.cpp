#include "LRT/Renderer/Framebuffer.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    Framebuffer::Framebuffer(const FramebufferSpec& spec)
        : m_Spec(spec) {
        Invalidate();
    }

    Framebuffer::~Framebuffer() {
        // glDeleteFramebuffers(1, &m_RendererID);
        // glDeleteTextures(1, &m_ColorAttachment);
        // glDeleteTextures(1, &m_DepthAttachment);
    }

    void Framebuffer::Invalidate() {
        if (m_RendererID) {
            // glDeleteFramebuffers(1, &m_RendererID);
            // glDeleteTextures(1, &m_ColorAttachment);
            // glDeleteTextures(1, &m_DepthAttachment);
        }

        // glGenFramebuffers(1, &m_RendererID);
        // glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        // Color attachment
        // glGenTextures(1, &m_ColorAttachment);
        // glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        // Depth attachment
        // glGenTextures(1, &m_DepthAttachment);
        // glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        // LRT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        LRT_TRACE("Framebuffer invalidated ({}x{})", m_Spec.Width, m_Spec.Height);
    }

    void Framebuffer::Bind() const {
        // glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        // glViewport(0, 0, m_Spec.Width, m_Spec.Height);
    }

    void Framebuffer::Unbind() const {
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Resize(u32 width, u32 height) {
        if (width == 0 || height == 0 || width > 8192 || height > 8192) {
            LRT_WARN("Attempted to resize framebuffer to {}x{}", width, height);
            return;
        }
        m_Spec.Width = width;
        m_Spec.Height = height;
        Invalidate();
    }

    Unique<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec) {
        return MakeUnique<Framebuffer>(spec);
    }

} // namespace LRT::Renderer
