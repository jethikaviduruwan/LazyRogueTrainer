#include "LRT/Renderer/Texture2D.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    Texture2D::Texture2D(const TextureSpec& spec)
        : m_Width(spec.Width), m_Height(spec.Height), m_Format(spec.Format) {
        // u32 internalFormat = 0, dataFormat = 0;
        // switch (spec.Format) {
        //     case TextureFormat::RGB8:   internalFormat = GL_RGB8;   dataFormat = GL_RGB;  break;
        //     case TextureFormat::RGBA8:  internalFormat = GL_RGBA8;  dataFormat = GL_RGBA; break;
        //     case TextureFormat::RGBA16F: internalFormat = GL_RGBA16F; dataFormat = GL_RGBA; break;
        //     default: break;
        // }
        // glGenTextures(1, &m_RendererID);
        // glBindTexture(GL_TEXTURE_2D, m_RendererID);
        // glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_Loaded = true;
        LRT_TRACE("Texture2D created ({}x{}, from spec)", m_Width, m_Height);
    }

    Texture2D::Texture2D(const std::string& path)
        : m_FilePath(path) {
        // Load image with stb_image
        // int w, h, channels;
        // stbi_set_flip_vertically_on_load(true);
        // stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
        // if (data) {
        //     m_Width = w; m_Height = h;
        //     glGenTextures(1, &m_RendererID);
        //     glBindTexture(GL_TEXTURE_2D, m_RendererID);
        //     glTexImage2D(...);
        //     if (spec.GenerateMips) glGenerateMipmap(GL_TEXTURE_2D);
        //     stbi_image_free(data);
        //     m_Loaded = true;
        // }

        LRT_DEBUG("Texture2D loaded from '{}'", path);
    }

    Texture2D::~Texture2D() {
        // glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::Bind(u32 slot) const {
        // glActiveTexture(GL_TEXTURE0 + slot);
        // glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture2D::Unbind() const {
        // glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::SetData(const void* data, u32 size) {
        // glBindTexture(GL_TEXTURE_2D, m_RendererID);
        // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    Unique<Texture2D> Texture2D::Create(const TextureSpec& spec) {
        return MakeUnique<Texture2D>(spec);
    }

    Unique<Texture2D> Texture2D::Create(const std::string& path) {
        return MakeUnique<Texture2D>(path);
    }

} // namespace LRT::Renderer
