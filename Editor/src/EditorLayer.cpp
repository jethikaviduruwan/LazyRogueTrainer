#include "EditorLayer.h"
#include "LRT/Core/Logger.h"
#include "LRT/Renderer/Renderer2D.h"
#include "LRT/Renderer/RenderCommand.h"

namespace LRTEditor {

    EditorLayer::EditorLayer()
        : Layer("EditorLayer") {}

    void EditorLayer::OnAttach() {
        LRT_INFO("EditorLayer attached");

        m_ActiveScene = LRT::MakeShared<LRT::ECS::Scene>("Editor Scene");

        // Setup camera
        f32 aspect = 16.0f / 9.0f;
        m_Camera = LRT::MakeUnique<LRT::Renderer::OrthographicCamera>(
            -aspect, aspect, -1.0f, 1.0f
        );

        // Setup framebuffer for viewport rendering
        LRT::Renderer::FramebufferSpec fbSpec;
        fbSpec.Width = 1600;
        fbSpec.Height = 900;
        m_Framebuffer = LRT::Renderer::Framebuffer::Create(fbSpec);

        m_SceneHierarchyPanel.SetScene(m_ActiveScene);

        LRT::Renderer::Renderer2D::Init();
    }

    void EditorLayer::OnDetach() {
        LRT::Renderer::Renderer2D::Shutdown();
        LRT_INFO("EditorLayer detached");
    }

    void EditorLayer::OnUpdate(LRT::f32 deltaTime) {
        // Resize framebuffer if viewport changed
        auto& fbSpec = m_Framebuffer->GetSpec();
        if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
            (fbSpec.Width != static_cast<LRT::u32>(m_ViewportSize.x) ||
             fbSpec.Height != static_cast<LRT::u32>(m_ViewportSize.y))) {
            m_Framebuffer->Resize(
                static_cast<LRT::u32>(m_ViewportSize.x),
                static_cast<LRT::u32>(m_ViewportSize.y)
            );
        }

        m_ActiveScene->Update(deltaTime);
    }

    void EditorLayer::OnRender() {
        LRT::Renderer::Renderer2D::ResetStats();

        m_Framebuffer->Bind();
        LRT::Renderer::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.18f, 1.0f });
        LRT::Renderer::RenderCommand::Clear();

        LRT::Renderer::Renderer2D::BeginScene(*m_Camera);

        // Render scene entities here
        // Example: draw a test quad
        LRT::Renderer::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f },
                                             { 0.2f, 0.8f, 0.3f, 1.0f });

        LRT::Renderer::Renderer2D::EndScene();
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender() {
        // ImGui docking space would be set up here
        // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        RenderMenuBar();
        RenderViewport();
        RenderToolbar();

        m_SceneHierarchyPanel.OnImGuiRender();
        m_ComponentInspector.OnImGuiRender();

        // Stats panel
        // ImGui::Begin("Renderer Stats");
        auto stats = LRT::Renderer::Renderer2D::GetStats();
        // ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        // ImGui::Text("Quads: %d", stats.QuadCount);
        // ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        // ImGui::End();
        (void)stats;
    }

    void EditorLayer::RenderMenuBar() {
        // ImGui::BeginMenuBar();
        // if (ImGui::BeginMenu("File")) {
        //     if (ImGui::MenuItem("New Scene", "Ctrl+N")) { /* ... */ }
        //     if (ImGui::MenuItem("Open Scene", "Ctrl+O")) { /* ... */ }
        //     if (ImGui::MenuItem("Save Scene", "Ctrl+S")) { /* ... */ }
        //     ImGui::Separator();
        //     if (ImGui::MenuItem("Exit")) { Application::Get().Close(); }
        //     ImGui::EndMenu();
        // }
        // ImGui::EndMenuBar();
    }

    void EditorLayer::RenderViewport() {
        // ImGui::Begin("Viewport");
        // m_ViewportFocused = ImGui::IsWindowFocused();
        // m_ViewportHovered = ImGui::IsWindowHovered();
        // auto viewportSize = ImGui::GetContentRegionAvail();
        // m_ViewportSize = { viewportSize.x, viewportSize.y };
        // u64 textureID = m_Framebuffer->GetColorAttachmentID();
        // ImGui::Image(reinterpret_cast<void*>(textureID), viewportSize, {0,1}, {1,0});
        // ImGui::End();
    }

    void EditorLayer::RenderToolbar() {
        // ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar);
        // Play / Pause / Stop buttons for runtime simulation
        // ImGui::End();
    }

} // namespace LRTEditor
