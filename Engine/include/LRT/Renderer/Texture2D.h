#pragma once

#include "LRT/Core/Types.h"
#include <string>

namespace LRT::Renderer {

    enum class TextureFormat : u8 {
        None = 0,
        RGB8,
        RGBA8,
        RGBA16F,
        Depth24Stencil8
    };

    struct TextureSpec {
        u32 Width = 1;
        u32 Height = 1;
        TextureFormat Format = TextureFormat::RGBA8;
        bool GenerateMips = true;
        bool WrapRepeat = true;
    };

    class Texture2D {
    public:
        explicit Texture2D(const TextureSpec& spec);
        Texture2D(const std::string& path);
        ~Texture2D();

        LRT_NON_COPYABLE(Texture2D)

        void Bind(u32 slot = 0) const;
        void Unbind() const;

        void SetData(const void* data, u32 size);

        u32 GetWidth() const { return m_Width; }
        u32 GetHeight() const { return m_Height; }
        u32 GetRendererID() const { return m_RendererID; }

        bool IsLoaded() const { return m_Loaded; }

        bool operator==(const Texture2D& other) const {
            return m_RendererID == other.m_RendererID;
        }

        static Unique<Texture2D> Create(const TextureSpec& spec);
        static Unique<Texture2D> Create(const std::string& path);

    private:
        u32 m_RendererID = 0;
        u32 m_Width = 0;
        u32 m_Height = 0;
        TextureFormat m_Format = TextureFormat::None;
        bool m_Loaded = false;
        std::string m_FilePath;
    };

} // namespace LRT::Renderer
