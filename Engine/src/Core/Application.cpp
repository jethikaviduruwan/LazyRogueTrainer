#include "LRT/Core/Application.h"
#include "LRT/Core/Logger.h"

namespace LRT {

    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpec& spec) {
        LRT_ASSERT_MSG(!s_Instance, "Application already exists");
        s_Instance = this;

        Logger::Init();
        LRT_INFO("Initializing LazyRogueTrainer Engine v{}", LRT_ENGINE_VERSION);

        WindowProps windowProps;
        windowProps.Title = spec.Name;
        windowProps.Width = spec.WindowWidth;
        windowProps.Height = spec.WindowHeight;
        m_Window = Window::Create(windowProps);
    }

    Application::~Application() {
        LRT_INFO("Shutting down engine");
        s_Instance = nullptr;
    }

    void Application::Run() {
        LRT_INFO("Engine main loop started");
        m_FrameTimer.Reset();

        while (m_Running) {
            m_DeltaTime = static_cast<f32>(m_FrameTimer.Elapsed());
            m_FrameTimer.Reset();

            CalculateFrameStats();

            if (!m_Minimized) {
                OnUpdate();
                OnRender();
            }

            m_Window->OnUpdate();
            m_FrameCount++;
        }
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::OnUpdate() {
        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate(m_DeltaTime);
        }
    }

    void Application::OnRender() {
        for (Layer* layer : m_LayerStack) {
            layer->OnRender();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        LRT_DEBUG("Pushed layer: {}", layer->GetName());
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        LRT_DEBUG("Pushed overlay: {}", overlay->GetName());
    }

    void Application::CalculateFrameStats() {
        m_FPSFrameCount++;
        m_FPSAccumulator += m_DeltaTime;
        if (m_FPSAccumulator >= 1.0f) {
            m_FPS = static_cast<f32>(m_FPSFrameCount) / m_FPSAccumulator;
            m_FPSFrameCount = 0;
            m_FPSAccumulator = 0.0f;
        }
    }

} // namespace LRT
