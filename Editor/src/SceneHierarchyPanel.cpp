#include "SceneHierarchyPanel.h"
#include "LRT/Core/Logger.h"

namespace LRTEditor {

    void SceneHierarchyPanel::SetScene(const LRT::Shared<LRT::ECS::Scene>& scene) {
        m_Scene = scene;
        m_SelectedEntity = LRT::NullEntity;
    }

    void SceneHierarchyPanel::OnImGuiRender() {
        // ImGui::Begin("Scene Hierarchy");

        if (m_Scene) {
            // ImGui::Text("Scene: %s", m_Scene->GetName().c_str());
            // ImGui::Text("Entities: %u", m_Scene->GetEntityCount());
            // ImGui::Separator();

            // for (auto entity : m_Scene->GetAllEntities()) {
            //     DrawEntityNode(entity);
            // }

            // Right-click context menu for creating entities
            // if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_NoOpenOverItems)) {
            //     if (ImGui::MenuItem("Create Empty Entity")) {
            //         m_Scene->CreateEntity();
            //     }
            //     ImGui::EndPopup();
            // }
        }

        // ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(LRT::EntityID entity) {
        // ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        // if (m_SelectedEntity == entity) flags |= ImGuiTreeNodeFlags_Selected;

        // std::string label = std::format("Entity {}", entity);
        // bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, "%s", label.c_str());

        // if (ImGui::IsItemClicked()) {
        //     m_SelectedEntity = entity;
        // }

        // // Delete entity popup
        // if (ImGui::BeginPopupContextItem()) {
        //     if (ImGui::MenuItem("Delete Entity")) {
        //         m_Scene->DestroyEntity(entity);
        //         if (m_SelectedEntity == entity) m_SelectedEntity = LRT::NullEntity;
        //     }
        //     ImGui::EndPopup();
        // }

        // if (opened) {
        //     ImGui::TreePop();
        // }
        (void)entity;
    }

} // namespace LRTEditor
