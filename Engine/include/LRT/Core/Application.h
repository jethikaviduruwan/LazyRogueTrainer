#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Core/Window.h"
#include "LRT/Core/LayerStack.h"
#include "LRT/Core/Timer.h"

namespace LRT {

    struct ApplicationSpec {
        std::string Name = "LazyRogueTrainer Application";
        u32 WindowWidth = 1280;
        u32 WindowHeight = 720;
    };

    class Application {
    public:
        explicit Application(const ApplicationSpec& spec);
        virtual ~Application();

        LRT_NON_COPYABLE(Application)

        void Run();
        void Close();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

        f32 GetDeltaTime() const { return m_DeltaTime; }
        f32 GetFPS() const { return m_FPS; }
        u64 GetFrameCount() const { return m_FrameCount; }

    private:
        void OnUpdate();
        void OnRender();
        void CalculateFrameStats();

        Unique<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;
        bool m_Minimized = false;

        Timer m_FrameTimer;
        f32 m_DeltaTime = 0.0f;
        f32 m_FPS = 0.0f;
        u64 m_FrameCount = 0;
        f32 m_FPSAccumulator = 0.0f;
        u32 m_FPSFrameCount = 0;

        static Application* s_Instance;
    };

    // Defined by the client
    Application* CreateApplication();

} // namespace LRT

