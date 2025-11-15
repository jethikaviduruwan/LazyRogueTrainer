#pragma once

#include "LRT/Core/LayerStack.h"
#include "LRT/ECS/Scene.h"
#include "LRT/Renderer/Camera.h"
#include "LRT/Renderer/Framebuffer.h"
#include "SceneHierarchyPanel.h"
#include "ComponentInspector.h"

namespace LRTEditor {

    class EditorLayer : public LRT::Layer {
    public:
        EditorLayer();
        ~EditorLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(LRT::f32 deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        void RenderMenuBar();
        void RenderViewport();
        void RenderToolbar();

        LRT::Shared<LRT::ECS::Scene> m_ActiveScene;
        LRT::Unique<LRT::Renderer::OrthographicCamera> m_Camera;
        LRT::Unique<LRT::Renderer::Framebuffer> m_Framebuffer;

        SceneHierarchyPanel m_SceneHierarchyPanel;
        ComponentInspector m_ComponentInspector;

        LRT::Math::Vec2 m_ViewportSize{ 0, 0 };
        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        // Gizmo state
        int m_GizmoType = -1; // -1 = no gizmo, 0 = translate, 1 = rotate, 2 = scale
    };

} // namespace LRTEditor
