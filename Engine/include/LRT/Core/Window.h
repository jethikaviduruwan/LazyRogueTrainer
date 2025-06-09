#pragma once

#include "LRT/Core/Types.h"
#include <string>
#include <functional>

namespace LRT {

    struct WindowProps {
        std::string Title;
        u32 Width;
        u32 Height;
        bool VSync;

        WindowProps(const std::string& title = "LazyRogueTrainer Engine",
                    u32 width = 1280, u32 height = 720, bool vsync = true)
            : Title(title), Width(width), Height(height), VSync(vsync) {}
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void()>;

        Window(const WindowProps& props);
        ~Window();

        LRT_NON_COPYABLE(Window)

        void OnUpdate();
        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }
        bool ShouldClose() const;

        u32 GetWidth() const { return m_Data.Width; }
        u32 GetHeight() const { return m_Data.Height; }
        f32 GetAspectRatio() const {
            return static_cast<f32>(m_Data.Width) / static_cast<f32>(m_Data.Height);
        }

        void* GetNativeWindow() const { return m_Window; }

        static Unique<Window> Create(const WindowProps& props = WindowProps());

    private:
        void Init(const WindowProps& props);
        void Shutdown();

        void* m_Window = nullptr;

        struct WindowData {
            std::string Title;
            u32 Width = 0;
            u32 Height = 0;
            bool VSync = false;
        };

        WindowData m_Data;
    };

} // namespace LRT

